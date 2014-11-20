#!/usr/bin/env python
from data_operation import file_operation
import re
import sys
import os


"""
Example:
python -m pair_match "new,delete;malloc,free" test_main.cpp
"""
def pair_match(pair_file, source_code):
    fpO = file_operation()
    pairs = []
    if os.path.exists(pair_file):
        pairs = fpO.read_lines(pair_file)
        pairs = [p.split(",") for p in pairs]
    else:
        try :
            pairs = [ p.split(",") for p in pair_file.split(";")]
        except Exception, e:
            print "Error input pair file.",e
            sys.exit()

    code = fpO.read(source_code)
    not_match = []

    #simply count the words in pairs
    for pair in pairs:
        count_result = []
        for word in pair :
            count_result.append(len(re.findall(word, code)))
            #print "Find %s %s." % (word, len(re.findall(word,code)))

        for count in count_result:
            if count != count_result[0]:
                not_match.append(pair)
                break
        print zip(pair, count_result)

    #details of variable pairs that not mathed
    for pair in not_match:
        res = {}
        not_match_words = []
        for word in pair:
            res[word] = re.findall(r"(.*?)=.*?%s.*?;"%word, code)
            #print word,"Here",res[word]
            words = [r.strip(" ").split(" ")[-1] for r in res[word]]
            for variable in words:
                if not re.search("%s.*?%s;" % (pair[1], variable), code):
                    print variable," not match!"
            break

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print "Usage: python %s pair_file code" % __file__
        sys.exit()
    pair_match(sys.argv[1], sys.argv[2])
