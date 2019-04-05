import curses
import os
import time

from threading import Thread

from os import listdir
from os.path import isfile, join
from curses import wrapper

from screen import ScreenEnvironment
from Panel import Panel
from Menu import Menu, MenuItem

def main(stdscr):


	class InputThread(Thread):
		def __init__(self,screen):
			Thread.__init__(self)
			self.screen = screen
			self.running = 1
			self.focus = 0
		def run(self):
			while self.running:
				if self.focus != 0 :
					self.inputProcessing()
		def inputProcessing(self):
			c = self.screen.getch()
			if c == ord('q'): self.endMainLoop()
			if c == ord('j'):
				self.focus.getFocusedMenu().nextItem()
				self.screen.refresh()
			if c == ord('k'):
				self.focus.getFocusedMenu().previousItem()
				self.screen.refresh()
			if c == ord('h'):
				self.focus.goLeft()
				self.screen.refresh()
			if c == ord('l'):
				self.focus.getFocusedMenu().moveIn()
				self.screen.refresh()
		def endMainLoop(self):
			self.running = 0
		def select(self,zone):
			self.focus = zone
	
	SE = ScreenEnvironment()
	SE.start()
	P = Panel(SE)

	stdscr.keypad(True)
	ITh = InputThread(SE.screen)
	ITh.select(P)
	#Threads can be started before main loop and stopped after it
	ITh.start()
	#Everything here occurs before end of InputThread
	
	ITh.join() #return when InputThread has ended



wrapper(main) #en cas d'erreur
#main(1)
