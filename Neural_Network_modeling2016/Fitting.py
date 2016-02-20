__author__ = 'jason'
import csv
import math
readerSub = csv.reader(file('/Users/jason/Desktop/finalDataSub.csv', 'rb'))
readerObj = csv.reader(file('/Users/jason/Desktop/finalDataObj.csv', 'rb'))
dataSub = []
dataObj = []
dataFinal = []
for line in readerSub:
    dataSub.append(line)
for line in readerObj:
    dataObj.append(line)
for i in range(0, len(dataObj)):
    distance1 = math.sqrt((float(dataObj[i][0])+0.01403)*(float(dataObj[i][0])+0.01403)+(float(dataSub[i][0])-0.01636)*(float(dataSub[i][0])-0.01636))
    distance2 = math.fabs((-0.8577*float(dataObj[i][0])+float(dataSub[i][0])-0.0284)/math.sqrt(0.8577*0.8577+1))
    dataFinal.append(math.sqrt(distance1*distance1-distance2*distance2))

writer = csv.writer(file('/Users/jason/Desktop/modeling/data/fittingOut.csv', 'wb'))
minValue = min(dataFinal)
maxValue = max(dataFinal)
for value in dataFinal:
    writer.writerow([(value-minValue)/(maxValue-minValue)])




