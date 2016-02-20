__author__ = 'jason'
import csv
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts import buildNetwork
import numpy as np
#read csv data:
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/filter_data_new2.csv', 'rb'))

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
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/filter_data_new2.csv', 'rb'))
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
ds9_20 = SupervisedDataSet(13, 2)
ds13_15 = SupervisedDataSet(13, 2)
ds9_16 = SupervisedDataSet(13, 2)
ds14_18 = SupervisedDataSet(13, 2)
ds19_20 = SupervisedDataSet(13, 2)
ds9_18 = SupervisedDataSet(13, 2)
ds17_18 = SupervisedDataSet(13, 2)
ds9_17 = SupervisedDataSet(13, 2)
ds14_19 = SupervisedDataSet(13, 2)
ds9_19 = SupervisedDataSet(13, 2)
ds9_14 = SupervisedDataSet(13, 2)
ds17_19 = SupervisedDataSet(13, 2)



for tuple in data_training_raw:
    tuple_data = []
    output_tmp9_20 = []
    for i in range(6, 21):
        if i == 9 or i == 20:
            output_tmp9_20.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    ds9_20.addSample(tuple_data, output_tmp9_20)
for tuple in data_training_raw:
    output_tmp13_15 = []
    tuple_data = []
    for i in range(6, 21):
        if i == 13 or i == 15: #here
                      #here
            output_tmp13_15.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds13_15.addSample(tuple_data, output_tmp13_15)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp9_16 = []
    for i in range(6, 21):
        if i == 9 or i == 16: #here
                      #here
            output_tmp9_16.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds9_16.addSample(tuple_data, output_tmp9_16)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp14_18 = []
    for i in range(6, 21):
        if i == 14 or i == 18: #here
                      #here
            output_tmp14_18.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds14_18.addSample(tuple_data, output_tmp14_18)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp19_20 = []
    for i in range(6, 21):
        if i == 19 or i == 20: #here
                      #here
            output_tmp19_20.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds19_20.addSample(tuple_data, output_tmp19_20)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp9_18 = []
    for i in range(6, 21):
        if i == 9 or i == 18: #here
                      #here
            output_tmp9_18.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds9_18.addSample(tuple_data, output_tmp9_18)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp17_18 = []
    for i in range(6, 21):
        if i == 17 or i == 18: #here
                      #here
            output_tmp17_18.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds17_18.addSample(tuple_data, output_tmp17_18)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp9_17 = []
    for i in range(6, 21):
        if i == 9 or i == 17: #here
                      #here
            output_tmp9_17.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds9_17.addSample(tuple_data, output_tmp9_17)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp14_19 = []
    for i in range(6, 21):
        if i == 14 or i == 19: #here
                      #here
            output_tmp14_19.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds14_19.addSample(tuple_data, output_tmp14_19)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp9_19 = []
    for i in range(6, 21):
        if i == 9 or i == 19: #here
                      #here
            output_tmp9_19.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds9_19.addSample(tuple_data, output_tmp9_19)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp9_14 = []
    for i in range(6, 21):
        if i == 9 or i == 14: #here
                      #here
            output_tmp9_14.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds9_14.addSample(tuple_data, output_tmp9_14)
for tuple in data_training_raw:
    tuple_data = []
    output_tmp17_19 = []
    for i in range(6, 21):
        if i == 17 or i == 19: #here
                      #here
            output_tmp17_19.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    #here                                   #here
    ds17_19.addSample(tuple_data, output_tmp17_19)


net9_20 = buildNetwork(13, 10, 2, bias=True)
trainer9_20 = BackpropTrainer(net9_20, ds9_20,learningrate=0.01)
error9_20 = trainer9_20.trainEpochs(300)

net13_15 = buildNetwork(13, 10, 2, bias=True)
trainer13_15 = BackpropTrainer(net13_15, ds13_15,learningrate=0.01)
error13_15 = trainer13_15.trainEpochs(300)

net9_16 = buildNetwork(13, 10, 2, bias=True)
trainer9_16 = BackpropTrainer(net9_16, ds9_16,learningrate=0.01)
error9_16 = trainer9_16.trainEpochs(300)

net14_18 = buildNetwork(13, 10, 2, bias=True)
trainer14_18 = BackpropTrainer(net14_18, ds14_18,learningrate=0.01)
error14_18 = trainer14_18.trainEpochs(300)

net19_20 = buildNetwork(13, 10, 2, bias=True)
trainer19_20 = BackpropTrainer(net19_20, ds19_20,learningrate=0.01)
error19_20 = trainer19_20.trainEpochs(300)

net9_18 = buildNetwork(13, 10, 2, bias=True)
trainer9_18 = BackpropTrainer(net9_18, ds9_18,learningrate=0.01)
error9_18 = trainer9_18.trainEpochs(300)

net17_18 = buildNetwork(13, 10, 2, bias=True)
trainer17_18 = BackpropTrainer(net17_18, ds17_18,learningrate=0.01)
error17_18 = trainer17_18.trainEpochs(300)

net9_17 = buildNetwork(13, 10, 2, bias=True)
trainer9_17 = BackpropTrainer(net9_17, ds9_17,learningrate=0.01)
error9_17 = trainer9_17.trainEpochs(300)

net14_19 = buildNetwork(13, 10, 2, bias=True)
trainer14_19 = BackpropTrainer(net14_19, ds14_19,learningrate=0.01)
error14_19 = trainer14_19.trainEpochs(300)

net9_19 = buildNetwork(13, 10, 2, bias=True)
trainer9_19 = BackpropTrainer(net9_19, ds9_19,learningrate=0.01)
error9_19 = trainer9_19.trainEpochs(300)

net9_14 = buildNetwork(13, 10, 2, bias=True)
trainer9_14 = BackpropTrainer(net9_14, ds9_14,learningrate=0.01)
error9_14 = trainer9_14.trainEpochs(300)

net17_19 = buildNetwork(13, 10, 2, bias=True)
trainer17_19 = BackpropTrainer(net17_19, ds17_19,learningrate=0.01)
error17_19 = trainer17_19.trainEpochs(300)

iterOut = -1
for line in data_fit:
    iterOut += 1
    input9_20_example = []
    output9_20_example = []
    input13_15_example = []
    output13_15_example = []
    input9_16_example = []
    output9_16_example = []
    input14_18_example = []
    output14_18_example = []
    input19_20_example = []
    output19_20_example = []
    input9_18_example = []
    output9_18_example = []
    input17_18_example = []
    output17_18_example = []
    input9_17_example = []
    output9_17_example = []
    input14_19_example = []
    output14_19_example = []
    input9_19_example = []
    output9_19_example = []
    input9_14_example = []
    output9_14_example = []
    input17_19_example = []
    output17_19_example = []
    nullAttr = []
    nullNum = 0
    #get the null num:
    iterIn = 0
    for value in line:
        if value == 'NULL' or value == 'PrivacySuppressed':
            nullAttr.append(iterIn)
            nullNum+=1
        iterIn+=1
    if nullNum == 2:
        if nullAttr[0] == 9 and nullAttr[1] == 20:
            for i in range(6,21):
                if i == 9 or i == 20:
                    continue
                else:
                    input9_20_example.append(float(line[i]))
            output9_20_example = net9_20.activate(input9_20_example)
            data_fit[iterOut][9] = float(output9_20_example[0])
            data_fit[iterOut][20] = float(output9_20_example[1])
        if nullAttr[0] == 13 and nullAttr[1] == 15:
            for i in range(6,21):
                if i == 13 or i == 15:
                    continue
                else:
                    input13_15_example.append(float(line[i]))
            output13_15_example = net13_15.activate(input13_15_example)
            data_fit[iterOut][13] = float(output13_15_example[0])
            data_fit[iterOut][15] = float(output13_15_example[1])
        if nullAttr[0] == 9 and nullAttr[1] == 16:
            for i in range(6,21):
                if i == 9 or i == 16:
                    continue
                else:
                    input9_16_example.append(float(line[i]))
            output9_16_example = net9_16.activate(input9_16_example)
            data_fit[iterOut][9] = float(output9_16_example[0])
            data_fit[iterOut][16] = float(output9_16_example[1])
        if nullAttr[0] == 14 and nullAttr[1] == 18:
            for i in range(6,21):
                if i == 14 or i == 18:
                    continue
                else:
                    input14_18_example.append(float(line[i]))
            output14_18_example = net14_18.activate(input14_18_example)
            data_fit[iterOut][14] = float(output14_18_example[0])
            data_fit[iterOut][18] = float(output14_18_example[1])
        if nullAttr[0] == 19 and nullAttr[1] == 20:
            for i in range(6,21):
                if i == 19 or i == 20:
                    continue
                else:
                    input19_20_example.append(float(line[i]))
            output19_20_example = net19_20.activate(input19_20_example)
            data_fit[iterOut][19] = float(output19_20_example[0])
            data_fit[iterOut][20] = float(output19_20_example[1])
        if nullAttr[0] == 9 and nullAttr[1] == 18:
            for i in range(6,21):
                if i == 9 or i == 18:
                    continue
                else:
                    input9_18_example.append(float(line[i]))
            output9_18_example = net9_18.activate(input9_18_example)
            data_fit[iterOut][9] = float(output9_18_example[0])
            data_fit[iterOut][18] = float(output9_18_example[1])
        if nullAttr[0] == 17 and nullAttr[1] == 18:
            for i in range(6,21):
                if i == 17 or i == 18:
                    continue
                else:
                    input17_18_example.append(float(line[i]))
            output17_18_example = net17_18.activate(input17_18_example)
            data_fit[iterOut][17] = float(output17_18_example[0])
            data_fit[iterOut][18] = float(output17_18_example[1])
        if nullAttr[0] == 9 and nullAttr[1] == 17:
            for i in range(6,21):
                if i == 9 or i == 17:
                    continue
                else:
                    input9_17_example.append(float(line[i]))
            output9_17_example = net9_17.activate(input9_17_example)
            data_fit[iterOut][9] = float(output9_17_example[0])
            data_fit[iterOut][17] = float(output9_17_example[1])
        if nullAttr[0] == 14 and nullAttr[1] == 19:
            for i in range(6,21):
                if i == 14 or i == 19:
                    continue
                else:
                    input14_19_example.append(float(line[i]))
            output14_19_example = net14_19.activate(input14_19_example)
            data_fit[iterOut][14] = float(output14_19_example[0])
            data_fit[iterOut][19] = float(output14_19_example[1])
        if nullAttr[0] == 9 and nullAttr[1] == 19:
            for i in range(6,21):
                if i == 9 or i == 19:
                    continue
                else:
                    input9_19_example.append(float(line[i]))
            output9_19_example = net9_19.activate(input9_19_example)
            data_fit[iterOut][9] = float(output9_19_example[0])
            data_fit[iterOut][19] = float(output9_19_example[1])
        if nullAttr[0] == 9 and nullAttr[1] == 14:
            for i in range(6,21):
                if i == 9 or i == 14:
                    continue
                else:
                    input9_14_example.append(float(line[i]))
            output9_14_example = net9_14.activate(input9_14_example)
            data_fit[iterOut][9] = float(output9_14_example[0])
            data_fit[iterOut][14] = float(output9_14_example[1])
        if nullAttr[0] == 17 and nullAttr[1] == 19:
            for i in range(6,21):
                if i == 17 or i == 19:
                    continue
                else:
                    input17_19_example.append(float(line[i]))
            output17_19_example = net17_19.activate(input17_19_example)
            data_fit[iterOut][17] = float(output17_19_example[0])
            data_fit[iterOut][19] = float(output17_19_example[1])

writer = csv.writer(file('/Users/jason/Desktop/modeling/data/DEBT_FILL_NULL.csv', 'wb'))
writer.writerow(attributes)
for school in data_fit:
    writer.writerow(school)