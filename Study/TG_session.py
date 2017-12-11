#-*- coding: utf-8 -*-
#code by Heonjin

import csv

class Count:
    def __init__(self):
        self.count = []
        self.value = []

class Count_byte:
    def __init__(self):
        self.src_ip = []
        self.dst_ip = []
        self.count = []

def data_store(se, result_src_ip,  result_src_port,result_dst_ip, result_dst_port, result_byte):
    for i in se:
        src = i[4].split('/')
        dst = i[5].split('/')

        # src_ip 뽑아내기
        if src[0] in result_src_ip.value:
            index = result_src_ip.value.index(src[0])
            result_src_ip.count[index] += 1
        else:
            result_src_ip.value.append(src[0])
            result_src_ip.count.append(1)

        # src_port
        if src[1] in result_src_port.value:
            index = result_src_port.value.index(src[1])
            result_src_port.count[index] += 1
        else:
            result_src_port.value.append(src[1])
            result_src_port.count.append(1)

        # dst_ip
        if dst[0] in result_dst_ip.value:
            index = result_dst_ip.value.index(dst[0])
            result_dst_ip.count[index] += 1
        else:
            result_dst_ip.value.append(dst[0])
            result_dst_ip.count.append(1)

        # dst_port
        if dst[1] in result_dst_port.value:
            index = result_dst_port.value.index(dst[1])
            result_dst_port.count[index] += 1
        else:
            result_dst_port.value.append(dst[1])
            result_dst_port.count.append(1)

        # byte 세기
        if src[0] in result_byte.src_ip:
            src_index = result_byte.src_ip.index(src[0])
            if result_byte.dst_ip[src_index] == dst[0]:
                result_byte.count[src_index] = int(result_byte.count[src_index]) + int(i[11])
        else:
            result_byte.src_ip.append(src[0])
            result_byte.dst_ip.append(dst[0])
            result_byte.count.append(int(i[11]))

def top_ip(result, dic, name):
    for i in zip(result.value, result.count):
        dic[i[0]] = i[1]
    s = dict(sorted(dic.items(), key=lambda k: k[1], reverse=True))
    result = Count()
    for k, v in s.items():
        result.value.append(k)
        result.count.append(v)

    print("============ %s ==============" %name)
    for i in range(5):
        print("%15s   %d"%(result.value[i], result.count[i]))

def top_byte(result, dic):
    for i in zip(zip(result.src_ip, result.dst_ip), result.count):
        dic[i[0]] = i[1]
    s5 = dict(sorted(dic.items(), key=lambda k: k[1], reverse=True))
    result = Count_byte()
    for k, v in s5.items():
        src, dst = k
        result.src_ip.append(src)
        result.dst_ip.append(dst)
        result.count.append(v)
    print("============ byte ============")
    for i in range(5):
        print("%15s → %-20s%-10d" %(result.src_ip[i] ,result.dst_ip[i] ,result.count[i]) )

def main():
    f = open("TG_session1.csv", 'r')  # TG_session.csv 파일 불러오기
    se = csv.reader(f)  # 파일 읽어오기

    result_src_ip = Count()
    result_src_port = Count()
    result_dst_ip = Count()
    result_dst_port = Count()
    result_byte = Count_byte()

    srcIP_dic = dict()
    srcPORT_dic = dict()
    dstIP_dic = dict()
    dstPORT_dic = dict()
    byte = dict()

    # 데이터 뽑기
    data_store(se, result_src_ip,  result_src_port,result_dst_ip, result_dst_port, result_byte)

    # top 5 뽑기
    top_ip(result_src_ip, srcIP_dic, "src ip")
    top_ip(result_src_port, srcPORT_dic, "src port")
    top_ip(result_dst_ip, dstIP_dic, "dst ip")
    top_ip(result_dst_port, dstPORT_dic, "dst port")
    top_byte(result_byte, byte)

    f.close()

if __name__ == '__main__':
    main()
