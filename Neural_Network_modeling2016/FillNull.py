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
#get the training data:
readerTraining = csv.reader(file('/Users/jason/Desktop/modeling/data/TrainingData.csv', 'rb'))
data_training_raw = []
for line in readerTraining:
    if readerTraining.line_num == 1:
        continue
    else:
        data_training_raw.append(line)
#construct NN for ONE NULL:
ds = SupervisedDataSet(14, 1)
ds1_RET = SupervisedDataSet(14, 1)
ds1_SAT = SupervisedDataSet(14, 1)
ds1_UG25 = SupervisedDataSet(14, 1)
ds1_gt = SupervisedDataSet(14, 1)
ds1_md = SupervisedDataSet(14, 1)
input_training = []
output_training = []
output_tmp = []
input_training_RET = []
output_training_RET = []
output_tmp_RET = []
input_training_SAT = []
output_training_SAT = []
output_tmp_SAT = []
input_training_UG25 = []
output_training_UG25 = []
output_tmp_UG25 = []
input_training_gt = []
output_training_gt = []
output_tmp_gt = []
input_training_md = []
output_training_md = []
output_tmp_md = []
for tuple in data_training_raw:
    tuple_data = []
    for i in range(6, 21):
        #GRAD_DEBT_MDN_SUPP:
        if i == 17:
            output_training.append(float(tuple[i]))
            output_tmp = [float(tuple[i])]
        else:
            tuple_data.append(float(tuple[i]))
    input_training.append(tuple_data)
    ds.addSample(tuple_data, output_tmp)
for tuple in data_training_raw:
    tuple_data = []
    for i in range(6, 21):
        #RET
        if i == 14:
            output_training_RET.append(float(tuple[i]))
            output_tmp_RET = [float(tuple[i])]
        else:
            tuple_data.append(float(tuple[i]))
    input_training_RET.append(tuple_data)
    ds1_RET.addSample(tuple_data, output_tmp_RET)
for tuple in data_training_raw:
    tuple_data = []
    for i in range(6, 21):
        #SAT
        if i == 9:
            output_training_SAT.append(float(tuple[i]))
            output_tmp_SAT = [float(tuple[i])]
        else:
            tuple_data.append(float(tuple[i]))
    input_training_SAT.append(tuple_data)
    ds1_SAT.addSample(tuple_data, output_tmp_SAT)
for tuple in data_training_raw:
    tuple_data = []
    for i in range(6, 21):
        #UG
        if i == 16:
            output_training_UG25.append(float(tuple[i]))
            output_tmp_UG25 = [float(tuple[i])]
        else:
            tuple_data.append(float(tuple[i]))
    input_training_UG25.append(tuple_data)
    ds1_UG25.addSample(tuple_data, output_tmp_UG25)
for tuple in data_training_raw:
    tuple_data = []
    for i in range(6, 21):
        #gt
        if i == 20:
            output_training_gt.append(float(tuple[i]))
            output_tmp_gt = [float(tuple[i])]
        else:
            tuple_data.append(float(tuple[i]))
    input_training_gt.append(tuple_data)
    ds1_gt.addSample(tuple_data, output_tmp_gt)
for tuple in data_training_raw:
    tuple_data = []
    for i in range(6, 21):
        #md
        if i == 19:
            output_training_md.append(float(tuple[i]))
            output_tmp_md = [float(tuple[i])]
        else:
            tuple_data.append(float(tuple[i]))
    input_training_md.append(tuple_data)
    ds1_md.addSample(tuple_data, output_tmp_md)


net = buildNetwork(14, 10, 1, bias=True)
trainer = BackpropTrainer(net, ds,learningrate=0.01)
error = trainer.trainEpochs(300)

net_RET = buildNetwork(14, 10, 1, bias=True)
trainer_RET = BackpropTrainer(net_RET, ds1_RET,learningrate=0.01)
error_RET = trainer_RET.trainEpochs(300)

net_SAT = buildNetwork(14, 10, 1, bias=True)
trainer_SAT = BackpropTrainer(net_SAT, ds1_SAT,learningrate=0.01)
error_SAT = trainer_SAT.trainEpochs(300)

net_UG = buildNetwork(14, 10, 1, bias=True)
trainer_UG = BackpropTrainer(net_UG, ds1_UG25,learningrate=0.01)
error_UG = trainer_UG.trainEpochs(300)

net_gt = buildNetwork(14, 10, 1, bias=True)
trainer_gt = BackpropTrainer(net_gt, ds1_gt,learningrate=0.01)
error_gt = trainer_gt.trainEpochs(300)

net_md = buildNetwork(14, 10, 1, bias=True)
trainer_md = BackpropTrainer(net_md, ds1_md,learningrate=0.01)
error_md = trainer_md.trainEpochs(300)

iterOut = -1
for line in data_fit:
    iterOut += 1
    input_example = []
    output_example = []
    input_example_RET = []
    output_example_RET = []
    input_example_SAT = []
    output_example_SAT = []
    input_example_UG = []
    output_example_UG = []
    input_example_gt = []
    output_example_gt = []
    input_example_md = []
    output_example_md = []
    nullAttr = ''
    nullNum = 0
    #get the null num:
    iterIn = 0
    for value in line:
        if value == 'NULL' or value == 'PrivacySuppressed':
            nullAttr+=(attributes[iterIn]+',')
            nullNum+=1
        iterIn+=1
    if nullNum == 1:
        if nullAttr == 'GRAD_DEBT_MDN_SUPP,':
            for i in range(6,21):
                if i == 17:
                    continue
                else:
                    input_example.append(float(line[i]))
            output_example = net.activate(input_example)
            #print(output_example)
            data_fit[iterOut][17] = float(output_example[0])
        if nullAttr == 'RET,':
            for i in range(6,21):
                if i == 14:
                    continue
                else:
                    input_example_RET.append(float(line[i]))
            output_example_RET = net_RET.activate(input_example_RET)
            #print(output_example_RET)
            data_fit[iterOut][14] = float(output_example_RET[0])
        if nullAttr == 'SAT_AVG,':
            for i in range(6,21):
                if i == 9:
                    continue
                else:
                    input_example_SAT.append(float(line[i]))
            output_example_SAT = net_SAT.activate(input_example_SAT)
            #print(output_example)
            data_fit[iterOut][9] = float(output_example_SAT[0])
        if nullAttr == 'UG25abv,':
            for i in range(6,21):
                if i == 16:
                    continue
                else:
                    input_example_UG.append(float(line[i]))
            output_example_UG = net_UG.activate(input_example_UG)
            #print(output_example)
            data_fit[iterOut][16] = float(output_example_UG[0])
        if nullAttr == 'gt_25k_p6,':
            for i in range(6,21):
                if i == 20:
                    continue
                else:
                    input_example_gt.append(float(line[i]))
            output_example_gt = net_gt.activate(input_example_gt)
            #print(output_example)
            data_fit[iterOut][20] = float(output_example_gt[0])
        if nullAttr == 'md_earn_wne_p10,':
            for i in range(6,21):
                if i == 19:
                    continue
                else:
                    input_example_md.append(float(line[i]))
            output_example_md = net_md.activate(input_example_md)
            #print(output_example)
            data_fit[iterOut][19] = float(output_example_md[0])

writer = csv.writer(file('/Users/jason/Desktop/modeling/data/DEBT_FILL_NULL.csv', 'wb'))
writer.writerow(attributes)
for school in data_fit:
    writer.writerow(school)