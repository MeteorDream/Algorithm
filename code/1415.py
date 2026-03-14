# -*- coding: utf-8 -*-

def getHappyString(n, k):
    # 计算总共有多少个开心字符串
    total = 3 * (2 ** (n - 1))
    
    # 如果k大于总数量，返回空字符串
    if k > total:
        return ""
    
    # 字符集
    chars = ['a', 'b', 'c']
    
    # 结果字符串
    result = []
    
    # 第一个字符的选择
    group_size = 2 ** (n - 1)
    first_char_index = (k - 1) // group_size
    result.append(chars[first_char_index])
    
    # 剩余字符的处理
    k = (k - 1) % group_size
    prev_char = chars[first_char_index]
    
    # 逐个确定后续字符
    for i in range(1, n):
        # 剩余的组合数
        remaining = 2 ** (n - 1 - i)
        
        # 当前字符在剩余字符中的索引
        char_index = k // remaining
        
        # 确保不与前一个字符相同
        if prev_char == 'a':
            # 可选字符是 'b', 'c'
            # 如果char_index是0，选择'b'；如果char_index是1，选择'c'
            current_char = 'b' if char_index == 0 else 'c'
        elif prev_char == 'b':
            # 可选字符是 'a', 'c'
            # 如果char_index是0，选择'a'；如果char_index是1，选择'c'
            current_char = 'a' if char_index == 0 else 'c'
        else:  # prev_char == 'c'
            # 可选字符是 'a', 'b'
            # 如果char_index是0，选择'a'；如果char_index是1，选择'b'
            current_char = 'a' if char_index == 0 else 'b'
        
        result.append(current_char)
        k = k % remaining
        prev_char = current_char
    
    return ''.join(result)