__author__ = 'jason'
import csv
from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts import buildNetwork
#read csv data:
reader = csv.reader(file('/Users/jason/Desktop/modeling/data/fillNull8.csv', 'rb'))

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
#get the training data:
readerTraining = csv.reader(file('/Users/jason/Desktop/modeling/data/Training-score.csv', 'rb'))
data_training_raw = []
for line in readerTraining:
    if readerTraining.line_num == 1:
        continue
    else:
        data_training_raw.append(line)
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#construct NN for TWO NULL:
ds1 = SupervisedDataSet(15, 1)

for tuple in data_training_raw:
    tuple_data = []
    output_tmp1 = []
    for i in range(6, 22):
        if i == 21:
            output_tmp1.append(float(tuple[i]))
        else:
            tuple_data.append(float(tuple[i]))
    ds1.addSample(tuple_data, output_tmp1)

net_1 = buildNetwork(15, 10, 1, bias=True)
trainer_1 = BackpropTrainer(net_1, ds1,learningrate=0.01)
error_1 = trainer_1.trainEpochs(1000)

iterOut = -1
for line in data_fit:
    iterOut += 1
    input_1_example = []
    output_1_example = []
    #get the null num:
    for i in range(6,21):
        input_1_example.append(float(line[i]))
    output_1_example = net_1.activate(input_1_example)
    data_fit[iterOut].append(float(output_1_example[0]))



writer = csv.writer(file('/Users/jason/Desktop/modeling/data/finalResult.csv', 'wb'))
writer.writerow(attributes)
for school in data_fit:
    writer.writerow(school)