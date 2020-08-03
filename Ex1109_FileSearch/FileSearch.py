def HaveKeyword(s, keyword):
    if keyword in s:
        return 1
    else:
        return 0

def search(fnames):
    rslt = []
    for fname in fnames:
        # Condition for searching
        if (HaveKeyword(fname, '1') and HaveKeyword(fname, '2'))\
            or (HaveKeyword(fname, '3') and not HaveKeyword(fname, '4')):
            rslt.append(fname)
    return rslt

fnames = ['1234.txt', '2345.txt', '2456.txt', '1357.txt'\
    , '5316.txt', '9281.txt']

rslt = search(fnames)

print('File name list:', fnames)
print('Search result:', rslt)
