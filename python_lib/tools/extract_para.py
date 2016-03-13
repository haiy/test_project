#!/Library/Frameworks/Python.framework/Versions/2.7/bin/python
#-*-coding:utf-8-*-
f = open("coff.txt")
ct = f.readlines()
f.close()
ct_2 = [l.strip("\n").split("\t") for l in ct]
#print(ct_2)
res = ""
for i in ct_2:
#	print(i)
	if len(i) == 2 and abs(float(i[1]))>0:
		res += str(i[0])+"*"+str(i[1])
		res += "+"

res = res.strip("+").replace('常量','1')
score = "1/(1+exp(-(%s))) "%res
res = "select *, %s as prediction_score, case when %s > 0.5 then 1 else 0  end as prediction_result from ${t1};" % (score, score)
print(res)
