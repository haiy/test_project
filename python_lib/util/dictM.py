#!/usr/bin/python

def common_dict_items(d1, d2):
    comm_keys = set(d1.keys()).intersection(set(d2.keys()))
    res_d = {}
    for k in comm_keys:
        res_d[k] = d1[k]
    return comm_keys
