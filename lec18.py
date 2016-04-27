import threading
import random
import time

rcount = 0
wcount = 0

class Reader(threading.Thread):
	def __init__(self, threadName):
		threading.Thread.__init__(self, name = threadName)  
		self.sleepTime = random.randrange(1,3)

	def run(self):
		global writeCountMutex
		global readCountMutex
		global writePriMutex
		global writeMutex
		global rcount
		writePriMutex.acquire()
		readCountMutex.acquire()
		if rcount == 0:
			writeMutex.acquire()
		rcount = rcount + 1
		readCountMutex.release()
		writePriMutex.release()

		print("Read Process" + str(self.name) + ": start")
		time.sleep(self.sleepTime)
		print("Read Process" + str(self.name) + ": end " + str(self.sleepTime) + "s")
		
		readCountMutex.acquire()
		rcount = rcount - 1
		if rcount == 0:
			writeMutex.release()
		readCountMutex.release()

class Writer(threading.Thread):
	def __init__(self, threadName):
		threading.Thread.__init__(self, name = threadName)  
		self.sleepTime = random.randrange(1,3)

	def run(self):
		global writeCountMutex
		global writePriMutex
		global writeMutex
		global wcount
		writeCountMutex.acquire()
		if wcount == 0:
			writePriMutex.acquire()
		wcount = wcount + 1
		writeCountMutex.release()
		writeMutex.acquire()
		print("Write Process" + str(self.name) + ": start")
		time.sleep(self.sleepTime)
		print("Write Process" + str(self.name) + ": end " + str(self.sleepTime) + "s")
		writeMutex.release()
		writeCountMutex.acquire()
		wcount = wcount - 1
		if wcount == 0:
			writePriMutex.release()
		writeCountMutex.release()
		

if __name__ == '__main__':
	threads = []
	readCountMutex = threading.Semaphore(1)
	writeCountMutex = threading.Semaphore(1)
	writeMutex = threading.Semaphore(1)
	writePriMutex = threading.Semaphore(1)
	for i in range(1,4):
		threads.append(Reader("Read"+str(i)))
		threads.append(Writer("Write"+str(i)))
	for thread in threads:
		thread.start()

