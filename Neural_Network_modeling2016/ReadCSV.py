__author__ = 'jason'
import csv
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull8.csv', 'rb'))
data = []
attributes = []
for line in reader:
    if reader.line_num == 1:
        attributes = line
    else:
        oneSchool = {}
        i = 0
        for value in line:
            oneSchool[attributes[i]] = value
            i+=1
        data.append(oneSchool)
#for scatter plot:
for school in data:
    print('d.push(['+school['SAT_AVG']+','+school['md_earn_wne_p10']+']);')
print("hah")

#print(data)
# max1 = 0
# max2 = 0
# min1 = 999999
# min2 = 999999
# for line in data:
#     if line[attributes[117]]!='NULL' and line[attributes[117]]!='PrivacySuppressed':
#         if float(line[attributes[117]]) < min1:
#             min1 = float(line[attributes[117]])
#         if float(line[attributes[117]]) > max1:
#             max1 = float(line[attributes[117]])
#     if line[attributes[118]]!='NULL' and line[attributes[118]]!='PrivacySuppressed':
#         if float(line[attributes[118]]) < min2:
#             min2 = float(line[attributes[118]])
#         if float(line[attributes[118]]) > max2:
#             max2 = float(line[attributes[118]])
#
# for line in data:
#     if line[attributes[117]]!='NULL' and line[attributes[118]]!='NULL' and line[attributes[117]]!='PrivacySuppressed' and line[attributes[118]]!='PrivacySuppressed':
#         my1 = (float(line[attributes[117]]) - min1)/(max1 - min1)
#         my2 = (float(line[attributes[118]]) - min2)/(max2 - min2)


#
#print(data)
# fout = open("/Users/jason/Desktop/attributes.json","w")
# for i in attributes:
#     fout.write(".hideAxis([\""+i+"\"])\n")
#SAT_AVG, UGDS, PCTPELL, PCTFLOAN, RPY_3YR_RT_SUPP, md_earn_wne_p10, gt_25k_p6


# #get the training data:
# trainingData = []
# for school in data:
#     breakable = False
#     for i in range(8, 12):
#         if school[attributes[i]] == 'NULL':
#             breakable = True
#             break
#     if breakable:
#         continue
#     for i in range(45, 83):
#         if school[attributes[i]] == 'NULL':
#             breakable = True
#             break
#     if breakable:
#         continue
#
#     # #NPT4
#     # for i in range(95, 108):
#     #     if school[attributes[i]] == 'NULL':
#     #         breakable = True
#     #         break
#     # if breakable:
#     #     continue
#     #PCTPELL
#     if school[attributes[108]] == 'NULL':
#         continue
#     # #RET_
#     # for i in range(109, 113):
#     #     if school[attributes[i]] == 'NULL':
#     #         breakable = True
#     #         break
#     # if breakable:
#     #     continue
#     #PCTFLOAN
#     if school[attributes[115]] == 'NULL':
#         continue
#     #UG25abv
#     if school[attributes[116]] == 'NULL':
#         continue
#     #GRAD_DEBT_
#     if (school[attributes[117]] == 'NULL' or school[attributes[117]] =='PrivacySuppressed') or (school[attributes[118]] == 'NULL' or school[attributes[118]] =='PrivacySuppressed'):
#         continue
#
#     for i in range(122, 124):
#         if school[attributes[i]] == 'NULL' or school[attributes[i]] =='PrivacySuppressed':
#             breakable = True
#             break
#     if breakable:
#         continue
#     if school[attributes[43]] == 'NULL' or school[attributes[84]]== 'NULL':
#         continue
#     trainingData.append(school)
#
# writer = csv.writer(file('/Users/jason/Desktop/modeling/data/training_data.csv', 'wb'))
# writer.writerow(attributes)
# for school in trainingData:
#     line = []
#     for attr in attributes:
#         line.append(school[attr])
#     writer.writerow(line)
# #print(trainingData)

#remove the tuple who has null number > 8
# filterData = []
# for school in data:
#     filterData.append(school)
# for school in data:
#     totalNullNum = 0
#     for value in school.values():
#         if value == 'NULL' or value == 'PrivacySuppressed':
#             totalNullNum+=1
#     if totalNullNum > 8:
#         filterData.remove(school)
#
# writer = csv.writer(file('/Users/jason/Desktop/modeling/data/filter_data_out.csv', 'wb'))
# writer.writerow(attributes)
# for school in filterData:
#     line = []
#     for attr in attributes:
#         line.append(school[attr])
#     writer.writerow(line)

#print(filterData)
