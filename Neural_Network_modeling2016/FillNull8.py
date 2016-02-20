__author__ = 'jason'
import csv
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts import buildNetwork
import numpy as np
#read csv data:
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull7.csv', 'rb'))

data = []
attributes = []
attrNullNum = {}
data_fit = []
#get the filter data:
for line in reader:
    if reader.line_num == 1:
        attributes = line
        for eachAttr in line:
            attrNullNum[eachAttr] = 0
    else:
        data_fit.append(line)
        oneSchool = {}
        i = 0
        for value in line:
            oneSchool[attributes[i]] = value
            if oneSchool[attributes[i]] == 'NULL' or oneSchool[attributes[i]] == 'PrivacySuppressed':
                attrNullNum[attributes[i]] += 1
            i+=1
        data.append(oneSchool)
#get the null attributes:
oneNull = {}
twoNull = {}
threeNull = {}
fourNull = {}
fiveNull = {}
sixNull = {}
sevenNull = {}
eightNull = {}
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull7.csv', 'rb'))
for line in reader:
    if reader.line_num == 1:
        continue
    else:
        iter = 0
        nullAttr = ''
        nullNum = 0
        for value in line:
            if value == 'NULL' or value == 'PrivacySuppressed':
                nullAttr+=(attributes[iter]+',')
                nullNum+=1
            iter+=1
        if nullNum == 1:
            if nullAttr not in oneNull.keys():
                oneNull[nullAttr] = 1
            else:
                oneNull[nullAttr]+=1
        if nullNum == 2:
            if nullAttr not in twoNull.keys():
                twoNull[nullAttr] = 1
            else:
                twoNull[nullAttr]+=1
        if nullNum == 3:
            if nullAttr not in threeNull.keys():
                threeNull[nullAttr] = 1
            else:
                threeNull[nullAttr]+=1
        if nullNum == 4:
            if nullAttr not in fourNull.keys():
                fourNull[nullAttr] = 1
            else:
                fourNull[nullAttr]+=1
        if nullNum == 5:
            if nullAttr not in fiveNull.keys():
                fiveNull[nullAttr] = 1
            else:
                fiveNull[nullAttr]+=1
        if nullNum == 6:
            if nullAttr not in sixNull.keys():
                sixNull[nullAttr] = 1
            else:
                sixNull[nullAttr]+=1
        if nullNum == 7:
            if nullAttr not in sevenNull.keys():
                sevenNull[nullAttr] = 1
            else:
                sevenNull[nullAttr]+=1
        if nullNum == 8:
            if nullAttr not in eightNull.keys():
                eightNull[nullAttr] = 1
            else:
                eightNull[nullAttr]+=1

# print("********two********")
# for elem in twoNull.keys():
#     print(elem+"\n")
# print("********three********")
# for elem in threeNull.keys():
#     print(elem+"\n")
# print("********four********")
# for elem in fourNull.keys():
#     print(elem+'\n')
# print("********five********")
# for elem in fiveNull.keys():
#     print(elem+'\n')
# print("********six********")
# for elem in sixNull.keys():
#     print(elem+'\n')
# print("********seven********")
# for elem in sevenNull.keys():
#     print(elem+'\n')
# print("********eight********")
# for elem in eightNull.keys():
#     print(elem+'\n')

#get the training data:
readerTraining = csv.reader(file('/Users/jason/Desktop/modeling/data/TrainingData.csv', 'rb'))
data_training_raw = []
for line in readerTraining:
    if readerTraining.line_num == 1:
        continue
    else:
        data_training_raw.append(line)
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#construct NN for TWO NULL:
ds1 = SupervisedDataSet(7, 8)
ds2 = SupervisedDataSet(7, 8)
ds3 = SupervisedDataSet(7, 8)
ds4 = SupervisedDataSet(7, 8)

magic1 = [9,12,14,16,17,18,19,20]
magic2 = [9,10,11,12,13,14,15,16]
magic3 = [9,13,14,15,17,18,19,20]
magic4 = [9,12,13,14,15,17,19,20]


for tuple in data_training_raw:
    tuple_data = []
    output_tmp1 = []
    for i in range(6, 21):
        if i == magic1[0] or i == magic1[1] or i == magic1[2] or i == magic1[3] or i == magic1[4] or i == magic1[5] or i == magic1[6] or i == magic1[7]:
            output_tmp1.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    ds1.addSample(tuple_data, output_tmp1)
for tuple in data_training_raw:
    output_tmp2 = []
    tuple_data = []
    for i in range(6, 21):
        if i == magic2[0] or i == magic2[1] or i == magic2[2] or i == magic2[3] or i == magic2[4] or i == magic2[5] or i == magic2[6] or i == magic2[7]:
                      #here
            output_tmp2.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds2.addSample(tuple_data, output_tmp2)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp3 = []
    for i in range(6, 21):
        if i == magic3[0] or i == magic3[1] or i == magic3[2] or i == magic3[3] or i == magic3[4] or i == magic3[5] or i == magic3[6] or i == magic3[7]:
                      #here
            output_tmp3.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds3.addSample(tuple_data, output_tmp3)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp4 = []
    for i in range(6, 21):
        if i == magic4[0] or i == magic4[1] or i == magic4[2] or i == magic4[3] or i == magic4[4] or i == magic4[5] or i == magic4[6] or i == magic4[7]:
                      #here
            output_tmp4.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds4.addSample(tuple_data, output_tmp4)

net_1 = buildNetwork(7, 10, 8, bias=True)
trainer_1 = BackpropTrainer(net_1, ds1,learningrate=0.01)
error_1 = trainer_1.trainEpochs(300)

net_2 = buildNetwork(7, 10, 8, bias=True)
trainer_2 = BackpropTrainer(net_2, ds2,learningrate=0.01)
error_2 = trainer_2.trainEpochs(300)

net_3 = buildNetwork(7, 10, 8, bias=True)
trainer_3 = BackpropTrainer(net_3, ds3,learningrate=0.01)
error_3 = trainer_3.trainEpochs(300)

net_4 = buildNetwork(7, 10, 8, bias=True)
trainer_4 = BackpropTrainer(net_4, ds4,learningrate=0.01)
error_4 = trainer_4.trainEpochs(300)


iterOut = -1
for line in data_fit:
    iterOut += 1
    input_1_example = []
    output_1_example = []
    input_2_example = []
    output_2_example = []
    input_3_example = []
    output_3_example = []
    input_4_example = []
    output_4_example = []
    nullAttr = []
    nullNum = 0
    #get the null num:
    iterIn = 0
    for value in line:
        if value == 'NULL' or value == 'PrivacySuppressed':
            nullAttr.append(iterIn)
            nullNum+=1
        iterIn+=1

    if nullNum == 8:
        if nullAttr[0] == magic1[0] and nullAttr[1] == magic1[1] and nullAttr[2] == magic1[2] and nullAttr[3] == magic1[3] and nullAttr[4] == magic1[4] and nullAttr[5] == magic1[5] and nullAttr[6] == magic1[6] and nullAttr[7] == magic1[7]:
            for i in range(6,21):
                if i == magic1[0] or i == magic1[1] or i == magic1[2] or i == magic1[3] or i == magic1[4] or i == magic1[5] or i == magic1[6] or i == magic1[7]:
                    continue
                else:
                    input_1_example.append(float(line[i]))
            output_1_example = net_1.activate(input_1_example)
            data_fit[iterOut][magic1[0]] = float(output_1_example[0])
            data_fit[iterOut][magic1[1]] = float(output_1_example[1])
            data_fit[iterOut][magic1[2]] = float(output_1_example[2])
            data_fit[iterOut][magic1[3]] = float(output_1_example[3])
            data_fit[iterOut][magic1[4]] = float(output_1_example[4])
            data_fit[iterOut][magic1[5]] = float(output_1_example[5])
            data_fit[iterOut][magic1[6]] = float(output_1_example[6])
            data_fit[iterOut][magic1[7]] = float(output_1_example[7])

        if nullAttr[0] == magic2[0] and nullAttr[1] == magic2[1] and nullAttr[2] == magic2[2] and nullAttr[3] == magic2[3] and nullAttr[4] == magic2[4] and nullAttr[5] == magic2[5] and nullAttr[6] == magic2[6] and nullAttr[7] == magic2[7]:
            for i in range(6,21):
                if i == magic2[0] or i == magic2[1] or i == magic2[2] or i == magic2[3] or i == magic2[4] or i == magic2[5] or i == magic2[6] or i == magic2[7]:
                    continue
                else:
                    input_2_example.append(float(line[i]))
            output_2_example = net_2.activate(input_2_example)
            data_fit[iterOut][magic2[0]]= float(output_2_example[0])
            data_fit[iterOut][magic2[1]] = float(output_2_example[1])
            data_fit[iterOut][magic2[2]] = float(output_2_example[2])
            data_fit[iterOut][magic2[3]] = float(output_2_example[3])
            data_fit[iterOut][magic2[4]] = float(output_2_example[4])
            data_fit[iterOut][magic2[5]] = float(output_2_example[5])
            data_fit[iterOut][magic2[6]] = float(output_2_example[6])
            data_fit[iterOut][magic2[7]] = float(output_2_example[7])


        if nullAttr[0] == magic3[0] and nullAttr[1] == magic3[1] and nullAttr[2] == magic3[2] and nullAttr[3] == magic3[3] and nullAttr[4] == magic3[4] and nullAttr[5] == magic3[5] and nullAttr[6] == magic3[6] and nullAttr[7] == magic3[7]:
            for i in range(6,21):
                if i == magic3[0] or i == magic3[1] or i == magic3[2] or i == magic3[3] or i == magic3[4] or i == magic3[5] or i == magic3[6] or i == magic3[7]:
                    continue
                else:
                    input_3_example.append(float(line[i]))
            output_3_example = net_3.activate(input_3_example)
            data_fit[iterOut][magic3[0]]= float(output_3_example[0])
            data_fit[iterOut][magic3[1]] = float(output_3_example[1])
            data_fit[iterOut][magic3[2]] = float(output_3_example[2])
            data_fit[iterOut][magic3[3]] = float(output_3_example[3])
            data_fit[iterOut][magic3[4]] = float(output_3_example[4])
            data_fit[iterOut][magic3[5]] = float(output_3_example[5])
            data_fit[iterOut][magic3[6]] = float(output_3_example[6])
            data_fit[iterOut][magic3[7]] = float(output_3_example[7])

        if nullAttr[0] == magic4[0] and nullAttr[1] == magic4[1] and nullAttr[2] == magic4[2] and nullAttr[3] == magic4[3] and nullAttr[4] == magic4[4] and nullAttr[5] == magic4[5] and nullAttr[6] == magic4[6] and nullAttr[7] == magic4[7]:
            for i in range(6,21):
                if i == magic4[0] or i == magic4[1] or i == magic4[2] or i == magic4[3] or i == magic4[4] or i == magic4[5] or i == magic4[6] or i == magic4[7]:
                    continue
                else:
                    input_4_example.append(float(line[i]))
            output_4_example = net_4.activate(input_4_example)
            data_fit[iterOut][magic4[0]]= float(output_4_example[0])
            data_fit[iterOut][magic4[1]] = float(output_4_example[1])
            data_fit[iterOut][magic4[2]] = float(output_4_example[2])
            data_fit[iterOut][magic4[3]] = float(output_4_example[3])
            data_fit[iterOut][magic4[4]] = float(output_4_example[4])
            data_fit[iterOut][magic4[5]] = float(output_4_example[5])
            data_fit[iterOut][magic4[6]] = float(output_4_example[6])
            data_fit[iterOut][magic4[7]] = float(output_4_example[7])




writer = csv.writer(file('/Users/jason/Desktop/modeling/data/fillNull8.csv', 'wb'))
writer.writerow(attributes)
for school in data_fit:
    writer.writerow(school)