file = open(".MyBots.rb", "r")
theList = file.readlines()
file2 = open("bots.rb", "a")
i = 14
while(i != 138):
	file2.write(theList[i])
	i +=1
file.close()
file2.close()