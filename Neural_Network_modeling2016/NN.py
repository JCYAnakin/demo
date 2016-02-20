from pybrain.datasets import SupervisedDataSet
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts import buildNetwork

ds = SupervisedDataSet(4, 2)
ds.addSample([0,0,1,0], [0,1])
ds.addSample([0,1,0,0], [1,2])
ds.addSample([1,0,0,0], [1,1])
ds.addSample([1,1,1,0], [0,0])

net     = buildNetwork(4, 5, 2, bias=True)
trainer = BackpropTrainer(net, ds,learningrate=0.01)

error  = trainer.trainEpochs(600)
for inp, tar in ds:
 print [net.activate(inp), tar]

