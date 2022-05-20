# -*- coding: utf-8 -*-
# File    : GetLeetCodeTitle.py
# Author  : MeteorDream
# Time    : 2022/05/17 19:42:33
# Updata  : 2022/05/17 23:19:11
# language: Python
# Software: Visual Studio Code

from typing import List
import requests
import os
import re
import json
import time
import argparse

user_agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.122 Safari/537.36"

# Reference:
# - https://gcyml.github.io/2019/03/03/Python%E7%88%AC%E5%8F%96Leetcode%E9%A2%98%E7%9B%AE%E5%8F%8AAC%E4%BB%A3%E7%A0%81/
# - https://wanakiki.github.io/2020/leetcode-spider/

def get_question_list(en) -> List:
    if en:
        url = "https://leetcode.com/api/problems/all/"
    else:
        url = "https://leetcode.cn/api/problems/all/"

    headers = {'User-Agent': user_agent, 'Connection': 'keep-alive'}
    resp = requests.get(url, headers = headers)
        
    question_list = json.loads(resp.content.decode('utf-8'))

    # print(f"There are {question_list['num_total']} questions")

    s = list()

    for question in question_list['stat_status_pairs']:
        question_id = question['stat']['question_id']
        question_slug = question['stat']['question__title_slug']
        question_title = question['stat']['question__title']
        
        level = question['difficulty']['level']
        if level == 1:
            level = 'Easy'
        elif level == 2:
            level = 'Medium'
        elif level == 3:
            level = 'Hard'
        else:
            level = 'Unknow'
        
        # paid_only = question['paid_only']

        # print(f"id = {question_id}, title = {question_title}, level = {level}, slug = {question_slug}, pay: {question['paid_only']}")
        s.append((question_id, question_title, level, question_slug, ))
    s.reverse()
    return s

def convert(src):
    Remove = [
        "</?p>",
        "</li>",
        "</?pre>",
        "</?ul>",
        "</?ol>",
        "\t",
    ]
    Replace = [
        ["</?code>", "`"],
        ["</?strong>", "**"],
        # ["<pre>", "```\n"],
        ["</?em>", "_"],
        # ["</pre>", "```"],
        ["<li>", "- "],
        ["<sup>", "^"],
        ["<sup>", "^"],
        ["&nbsp;", " "],
        ["&quot;", '"'],
        ["&lt;", '<'],
        ["&gt;", '>'],
        [' \n', ''],
        ["<sup>", '^{'],
        ["</sup>", '}'],
        ["<sub>", '^{'],
        ["</sub>", '}'],
        ['\n\n\n', '\n\n'],
        ['\n\n\n', '\n\n'],
    ]
    # pre内部预处理
    def remove_label_in_pre(matched):
        tmp = matched.group()
        tmp = re.sub("<[^>p]*>", "", tmp)   # 不匹配>与p
        return tmp
    src = re.sub("<pre>[\s\S]*?</pre>", remove_label_in_pre, src)   # 注意此处非贪心匹配，因为可能有多个示例
    # 可以直接删除的标签
    for curPattern in Remove:
        src = re.sub(curPattern, "", src)
    # 需要替换内容的标签
    for curPattern, curRepl in Replace:
        src = re.sub(curPattern, curRepl, src)
    return src

def conv_sq(sq, en=False):
    """ Get SimilarQuestions """
    ans = list()
    cnt = dict()
    cot = list()
    for c in sq:
        if c == '{':
            cnt = dict()
            cot = list()
        elif c == ',':
            s = "".join(cot)
            s = s.split(':')
            assert len(s) == 2, f"Error: {s}"
            cnt[s[0].strip().replace('\"', '')] = s[1].strip().replace('\"', '').encode('utf-8').decode('unicode-escape')
            cot = list()
        elif c == '}':
            s = "".join(cot)
            s = s.split(':')
            assert len(s) == 2, f"Error: {s}"
            cnt[s[0].strip().replace('\"', '')] = s[1].strip().replace('\"', '').encode('utf-8').decode('unicode-escape')
            ans.append(cnt)
        else:
            cot.append(c)
    url = "https://leetcode.com/problems/" if en else "https://leetcode.cn/problems/"
    return "\n".join("- [{} ({})]({})".format((s['title'] if en else s['translatedTitle']), (s['difficulty'] if en else '简单' if s['difficulty'] == 'Easy' else '困难' if s['difficulty'] == 'Hard' else '中等'), url + s['titleSlug'] + '/') for s in ans)

def get_yaml_title(id, title):
    ans = [
        "---",
        "title: {}".format(f'『LeetCode』 {id} {title}'),
        "date: {}".format(time.strftime("%Y-%m-%d %H:%M:%S")),
        "categories:",
        "- [LeetCode]",
        "tags: [LeetCode]", 
        "---",
        ""
    ]
    return "\n".join(ans)

def get_problem_content(slug):
    # TODO: Default https://leetcode.cn not https://leetcode.com (english) because cn can also get english information
    url = "https://leetcode.cn/graphql"
    params = {'operationName': "getQuestionDetail",
                'variables': {'titleSlug': slug},
                'query': '''query getQuestionDetail($titleSlug: String!) {
            question(titleSlug: $titleSlug) {
                title
                translatedTitle
                difficulty
                questionId
                translatedContent
                content
                similarQuestions
            }
        }'''
    }
    json_data = json.dumps(params).encode('utf8')   
    headers = {'User-Agent': user_agent, 'Connection':
               'keep-alive', 'Content-Type': 'application/json',
               'Referer': 'https://leetcode.cn/problems/' + slug}
    resp = requests.post(url, data=json_data, headers=headers, timeout=10)
    resp.encoding = 'utf-8'
    content = resp.json()
    # print(content)
    question = content['data']['question']
    # fh = open('{test}.md', 'w', encoding='utf-8')
    # fh.writelines(convert(question['translatedContent']))
    # fh.close()
    return question

def get_LeetCode_List(en=False):
    """ If en is True, get English else get Chinese """
    if en:
        md_head = '| Id | Question | Difficulty |\n| :---: | :---: | :---: |\n'
        url = "https://leetcode.com/problems/"
    else:
        md_head = '| 编号 | 题目 | 难度 |\n| :---: | :---: | :---: |\n'
        url = "https://leetcode.cn/problems/"
    ql = get_question_list(en)
    with open("LeetCode_List.md", 'wt') as f:
        f.write(md_head)
        for id, title, level, slug in ql:
            f.write(f"| {id} | [{title.strip()}]({url + slug.strip() + '/'}) | {level} |\n")
        f.write('\n')
    return ql

def get_LeetCode_question(slug: str, en: bool):
    url = "https://leetcode.com/problems/" if en else "https://leetcode.cn/problems/"
    content = get_problem_content(slug)
    title = content['title'] if en else content['translatedTitle']
    difficulty = content['difficulty']
    if not en:
        difficulty = '简单' if difficulty == 'Easy' else '困难' if difficulty == 'Hard' else '中等'
    id = content['questionId']
    info = content['content'] if en else content['translatedContent']
    ques_info = convert(info)
    similarQuestions = conv_sq(content['similarQuestions'], en)
    md_title = f'{id}{title}({difficulty}).md'
    with open(md_title, 'wt', encoding='utf-8') as f:
        f.write(get_yaml_title(id, title))
        f.write("## 题目\n\n")
        f.write("[{}. {}]({})\n\n".format(id, title, url + slug + '/'))
        f.write("<!--more-->\n\n")
        f.write(ques_info)
        f.write("\n")
        f.write("## 相似题目\n\n")
        f.write(similarQuestions)
        f.write("\n\n")
        f.write("---\n\n")
        f.write("## 题解\n\n")
        f.write("[【{}】]()\n\n".format(title))
        f.write("```Python\n# Code language: Python\n\n```\n\n")
        f.write("```Java\n// Code language: Java\n\n```\n\n")
        f.write("```Cpp\n// Code language: Cpp\n\n```\n\n")
        f.write("- 时间复杂度: $O(n)$\n")
        f.write("- 空间复杂度: $O(1)$\n")
    return

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Get LeetCode question list or get question information to markdown file.")
    parser.add_argument('-g', '--get', action='store_true', help='Add the argument mean get LeetCode list.')
    parser.add_argument('-e', '--en', action='store_true', help="Add the argument mean get information from english web.")
    parser.add_argument('-t', type=int, default=[], nargs='+', help="The number of questions you want to get (Can more than one, split by space).")
    args = parser.parse_args()

    if args.get:
        ql = get_LeetCode_List(args.en)
    else:
        ql = get_question_list(args.en)
    

    id2slug = {id: slug for id, title, level, slug in ql}

    for t in args.t:
        get_LeetCode_question(id2slug[t], args.en)