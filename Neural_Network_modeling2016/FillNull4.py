__author__ = 'jason'
import csv
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts import buildNetwork
import numpy as np
#read csv data:
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull3.csv', 'rb'))

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
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull3.csv', 'rb'))
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
ds1 = SupervisedDataSet(11, 4)
ds2 = SupervisedDataSet(11, 4)
ds3 = SupervisedDataSet(11, 4)
ds4 = SupervisedDataSet(11, 4)
ds5 = SupervisedDataSet(11, 4)
ds6 = SupervisedDataSet(11, 4)
ds7 = SupervisedDataSet(11, 4)
ds8 = SupervisedDataSet(11, 4)
ds9 = SupervisedDataSet(11, 4)
ds10 = SupervisedDataSet(11, 4)
ds11 = SupervisedDataSet(11, 4)
ds12 = SupervisedDataSet(11, 4)

magic1 = [8,9,17,18]
magic2 = [9,14,17,18]
magic3 = [9,18,19,20]
magic4 = [9,14,19,20]
magic5 = [9,14,17,20]
magic6 = [9,14,17,19]
magic7 = [9,17,18,20]
magic8 = [9,16,17,18]
magic9 = [17,18,19,20]
magic10 = [16,18,19,20]
magic11 = [9,17,18,19]
magic12 = [9,17,19,20]

for tuple in data_training_raw:
    tuple_data = []
    output_tmp1 = []
    for i in range(6, 21):
        if i == magic1[0] or i == magic1[1] or i == magic1[2] or i == magic1[3]:
            output_tmp1.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    ds1.addSample(tuple_data, output_tmp1)
for tuple in data_training_raw:
    output_tmp2 = []
    tuple_data = []
    for i in range(6, 21):
        if i == magic2[0] or i == magic2[1] or i == magic2[2] or i == magic2[3]:
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
        if i == magic3[0] or i == magic3[1] or i == magic3[2] or i == magic3[3]:
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
        if i == magic4[0] or i == magic4[1] or i == magic4[2] or i == magic4[3]:
                      #here
            output_tmp4.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds4.addSample(tuple_data, output_tmp4)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp5 = []
    for i in range(6, 21):
        if i == magic5[0] or i == magic5[1] or i == magic5[2] or i == magic5[3]:
                      #here
            output_tmp5.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds5.addSample(tuple_data, output_tmp5)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp6 = []
    for i in range(6, 21):
        if i == magic6[0] or i == magic6[1] or i == magic6[2] or i == magic6[3]:
                      #here
            output_tmp6.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds6.addSample(tuple_data, output_tmp6)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp7 = []
    for i in range(6, 21):
        if i == magic7[0] or i == magic7[1] or i == magic7[2] or i == magic7[3]:
                      #here
            output_tmp7.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds7.addSample(tuple_data, output_tmp7)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp8 = []
    for i in range(6, 21):
        if i == magic8[0] or i == magic8[1] or i == magic8[2] or i == magic8[3]:
                      #here
            output_tmp8.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds8.addSample(tuple_data, output_tmp8)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp9 = []
    for i in range(6, 21):
        if i == magic9[0] or i == magic9[1] or i == magic9[2] or i == magic9[3]:
                      #here
            output_tmp9.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds9.addSample(tuple_data, output_tmp9)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp10 = []
    for i in range(6, 21):
        if i == magic10[0] or i == magic10[1] or i == magic10[2] or i == magic10[3]:
                      #here
            output_tmp10.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds10.addSample(tuple_data, output_tmp10)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp11 = []
    for i in range(6, 21):
        if i == magic11[0] or i == magic11[1] or i == magic11[2] or i == magic11[3]:
                      #here
            output_tmp11.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds11.addSample(tuple_data, output_tmp11)

for tuple in data_training_raw:
    tuple_data = []
    output_tmp12 = []
    for i in range(6, 21):
        if i == magic12[0] or i == magic12[1] or i == magic12[2] or i == magic12[3]:
                      #here
            output_tmp12.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds12.addSample(tuple_data, output_tmp12)

net_1 = buildNetwork(11, 10, 4, bias=True)
trainer_1 = BackpropTrainer(net_1, ds1,learningrate=0.01)
error_1 = trainer_1.trainEpochs(300)

net_2 = buildNetwork(11, 10, 4, bias=True)
trainer_2 = BackpropTrainer(net_2, ds2,learningrate=0.01)
error_2 = trainer_2.trainEpochs(300)

net_3 = buildNetwork(11, 10, 4, bias=True)
trainer_3 = BackpropTrainer(net_3, ds3,learningrate=0.01)
error_3 = trainer_3.trainEpochs(300)

net_4 = buildNetwork(11, 10, 4, bias=True)
trainer_4 = BackpropTrainer(net_4, ds4,learningrate=0.01)
error_4 = trainer_4.trainEpochs(300)

net_5 = buildNetwork(11, 10, 4, bias=True)
trainer_5 = BackpropTrainer(net_5, ds5,learningrate=0.01)
error_5 = trainer_5.trainEpochs(300)

net_6 = buildNetwork(11, 10, 4, bias=True)
trainer_6 = BackpropTrainer(net_6, ds6,learningrate=0.01)
error_6 = trainer_6.trainEpochs(300)

net_7 = buildNetwork(11, 10, 4, bias=True)
trainer_7 = BackpropTrainer(net_7, ds7,learningrate=0.01)
error_7 = trainer_7.trainEpochs(300)

net_8 = buildNetwork(11, 10, 4, bias=True)
trainer_8 = BackpropTrainer(net_8, ds8,learningrate=0.01)
error_8 = trainer_8.trainEpochs(300)

net_9 = buildNetwork(11, 10, 4, bias=True)
trainer_9 = BackpropTrainer(net_9, ds9,learningrate=0.01)
error_9 = trainer_9.trainEpochs(300)

net_10 = buildNetwork(11, 10, 4, bias=True)
trainer_10 = BackpropTrainer(net_10, ds10,learningrate=0.01)
error_10 = trainer_10.trainEpochs(300)

net_11 = buildNetwork(11, 10, 4, bias=True)
trainer_11 = BackpropTrainer(net_11, ds11,learningrate=0.01)
error_11 = trainer_11.trainEpochs(300)

net_12 = buildNetwork(11, 10, 4, bias=True)
trainer_12 = BackpropTrainer(net_12, ds12,learningrate=0.01)
error_12 = trainer_12.trainEpochs(300)


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
    input_5_example = []
    output_5_example = []
    input_6_example = []
    output_6_example = []
    input_7_example = []
    output_7_example = []
    input_8_example = []
    output_8_example = []
    input_9_example = []
    output_9_example = []
    input_10_example = []
    output_10_example = []
    input_11_example = []
    output_11_example = []
    input_12_example = []
    output_12_example = []
    nullAttr = []
    nullNum = 0
    #get the null num:
    iterIn = 0
    for value in line:
        if value == 'NULL' or value == 'PrivacySuppressed':
            nullAttr.append(iterIn)
            nullNum+=1
        iterIn+=1

    if nullNum == 4:
        if nullAttr[0] == magic1[0] and nullAttr[1] == magic1[1] and nullAttr[2] == magic1[2] and nullAttr[3] == magic1[3]:
            for i in range(6,21):
                if i == magic1[0] or i == magic1[1] or i == magic1[2] or i == magic1[3]:
                    continue
                else:
                    input_1_example.append(float(line[i]))
            output_1_example = net_1.activate(input_1_example)
            data_fit[iterOut][magic1[0]] = float(output_1_example[0])
            data_fit[iterOut][magic1[1]] = float(output_1_example[1])
            data_fit[iterOut][magic1[2]] = float(output_1_example[2])
            data_fit[iterOut][magic1[3]] = float(output_1_example[3])

        if nullAttr[0] == magic2[0] and nullAttr[1] == magic2[1] and nullAttr[2] == magic2[2] and nullAttr[3] == magic2[3]:
            for i in range(6,21):
                if i == magic2[0] or i == magic2[1] or i == magic2[2] or i == magic2[3]:
                    continue
                else:
                    input_2_example.append(float(line[i]))
            output_2_example = net_2.activate(input_2_example)
            data_fit[iterOut][magic2[0]]= float(output_2_example[0])
            data_fit[iterOut][magic2[1]] = float(output_2_example[1])
            data_fit[iterOut][magic2[2]] = float(output_2_example[2])
            data_fit[iterOut][magic2[3]] = float(output_2_example[3])

        if nullAttr[0] == magic3[0] and nullAttr[1] == magic3[1] and nullAttr[2] == magic3[2] and nullAttr[3] == magic3[3]:
            for i in range(6,21):
                if i == magic3[0] or i == magic3[1] or i == magic3[2] or i == magic3[3]:
                    continue
                else:
                    input_3_example.append(float(line[i]))
            output_3_example = net_3.activate(input_3_example)
            data_fit[iterOut][magic3[0]]= float(output_3_example[0])
            data_fit[iterOut][magic3[1]] = float(output_3_example[1])
            data_fit[iterOut][magic3[2]] = float(output_3_example[2])
            data_fit[iterOut][magic3[3]] = float(output_3_example[3])

        if nullAttr[0] == magic4[0] and nullAttr[1] == magic4[1] and nullAttr[2] == magic4[2] and nullAttr[3] == magic4[3]:
            for i in range(6,21):
                if i == magic4[0] or i == magic4[1] or i == magic4[2] or i == magic4[3]:
                    continue
                else:
                    input_4_example.append(float(line[i]))
            output_4_example = net_4.activate(input_4_example)
            data_fit[iterOut][magic4[0]]= float(output_4_example[0])
            data_fit[iterOut][magic4[1]] = float(output_4_example[1])
            data_fit[iterOut][magic4[2]] = float(output_4_example[2])
            data_fit[iterOut][magic4[3]] = float(output_4_example[3])

        if nullAttr[0] == magic5[0] and nullAttr[1] == magic5[1] and nullAttr[2] == magic5[2] and nullAttr[3] == magic5[3]:
            for i in range(6,21):
                if i == magic5[0] or i == magic5[1] or i == magic5[2] or i == magic5[3]:
                    continue
                else:
                    input_5_example.append(float(line[i]))
            output_5_example = net_5.activate(input_5_example)
            data_fit[iterOut][magic5[0]]= float(output_5_example[0])
            data_fit[iterOut][magic5[1]] = float(output_5_example[1])
            data_fit[iterOut][magic5[2]] = float(output_5_example[2])
            data_fit[iterOut][magic5[3]] = float(output_5_example[3])

        if nullAttr[0] == magic6[0] and nullAttr[1] == magic6[1] and nullAttr[2] == magic6[2] and nullAttr[3] == magic6[3]:
            for i in range(6,21):
                if i == magic6[0] or i == magic6[1] or i == magic6[2] or i == magic6[3]:
                    continue
                else:
                    input_6_example.append(float(line[i]))
            output_6_example = net_6.activate(input_6_example)
            data_fit[iterOut][magic6[0]]= float(output_6_example[0])
            data_fit[iterOut][magic6[1]] = float(output_6_example[1])
            data_fit[iterOut][magic6[2]] = float(output_6_example[2])
            data_fit[iterOut][magic6[3]] = float(output_6_example[3])

        if nullAttr[0] == magic7[0] and nullAttr[1] == magic7[1] and nullAttr[2] == magic7[2] and nullAttr[3] == magic7[3]:
            for i in range(6,21):
                if i == magic7[0] or i == magic7[1] or i == magic7[2] or i == magic7[3]:
                    continue
                else:
                    input_7_example.append(float(line[i]))
            output_7_example = net_7.activate(input_7_example)
            data_fit[iterOut][magic7[0]]= float(output_7_example[0])
            data_fit[iterOut][magic7[1]] = float(output_7_example[1])
            data_fit[iterOut][magic7[2]] = float(output_7_example[2])
            data_fit[iterOut][magic7[3]] = float(output_7_example[3])

        if nullAttr[0] == magic8[0] and nullAttr[1] == magic8[1] and nullAttr[2] == magic8[2] and nullAttr[3] == magic8[3]:
            for i in range(6,21):
                if i == magic8[0] or i == magic8[1] or i == magic8[2] or i == magic8[3]:
                    continue
                else:
                    input_8_example.append(float(line[i]))
            output_8_example = net_8.activate(input_8_example)
            data_fit[iterOut][magic8[0]] = float(output_8_example[0])
            data_fit[iterOut][magic8[1]] = float(output_8_example[1])
            data_fit[iterOut][magic8[2]] = float(output_8_example[2])
            data_fit[iterOut][magic8[3]] = float(output_8_example[3])

        if nullAttr[0] == magic9[0] and nullAttr[1] == magic9[1] and nullAttr[2] == magic9[2] and nullAttr[3] == magic9[3]:
            for i in range(6,21):
                if i == magic9[0] or i == magic9[1] or i == magic9[2] or i == magic9[3]:
                    continue
                else:
                    input_9_example.append(float(line[i]))
            output_9_example = net_9.activate(input_9_example)
            data_fit[iterOut][magic9[0]]= float(output_9_example[0])
            data_fit[iterOut][magic9[1]] = float(output_9_example[1])
            data_fit[iterOut][magic9[2]] = float(output_9_example[2])
            data_fit[iterOut][magic9[3]] = float(output_9_example[3])

        if nullAttr[0] == magic10[0] and nullAttr[1] == magic10[1] and nullAttr[2] == magic10[2] and nullAttr[3] == magic10[3]:
            for i in range(6,21):
                if i == magic10[0] or i == magic10[1] or i == magic10[2] or i == magic10[3]:
                    continue
                else:
                    input_10_example.append(float(line[i]))
            output_10_example = net_10.activate(input_10_example)
            data_fit[iterOut][magic10[0]] = float(output_10_example[0])
            data_fit[iterOut][magic10[1]] = float(output_10_example[1])
            data_fit[iterOut][magic10[2]] = float(output_10_example[2])
            data_fit[iterOut][magic10[3]] = float(output_10_example[3])

        if nullAttr[0] == magic11[0] and nullAttr[1] == magic11[1] and nullAttr[2] == magic11[2] and nullAttr[3] == magic11[3]:
            for i in range(6,21):
                if i == magic11[0] or i == magic11[1] or i == magic11[2] or i == magic11[3]:
                    continue
                else:
                    input_11_example.append(float(line[i]))
            output_11_example = net_11.activate(input_11_example)
            data_fit[iterOut][magic11[0]]= float(output_11_example[0])
            data_fit[iterOut][magic11[1]] = float(output_11_example[1])
            data_fit[iterOut][magic11[2]] = float(output_11_example[2])
            data_fit[iterOut][magic11[3]] = float(output_11_example[3])

        if nullAttr[0] == magic12[0] and nullAttr[1] == magic12[1] and nullAttr[2] == magic12[2] and nullAttr[3] == magic12[3]:
            for i in range(6,21):
                if i == magic12[0] or i == magic12[1] or i == magic12[2] or i == magic12[3]:
                    continue
                else:
                    input_12_example.append(float(line[i]))
            output_12_example = net_12.activate(input_12_example)
            data_fit[iterOut][magic12[0]]= float(output_12_example[0])
            data_fit[iterOut][magic12[1]] = float(output_12_example[1])
            data_fit[iterOut][magic12[2]] = float(output_12_example[2])
            data_fit[iterOut][magic12[3]] = float(output_12_example[3])


writer = csv.writer(file('/Users/jason/Desktop/modeling/data/DEBT_FILL_NULL4out.csv', 'wb'))
writer.writerow(attributes)
for school in data_fit:
    writer.writerow(school)