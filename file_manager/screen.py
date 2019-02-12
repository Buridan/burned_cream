import time
import curses

class ScreenEnvironment():
	def __init__(self):
		self.screen = curses.initscr()
		self.initCursesOptions()
		self.h,self.w  = self.screen.getmaxyx()
		self.x = 0
		self.y = 0
	def start(self):
		curses.newwin(self.h,self.w,self.x,self.y)
		#self.screen.addstr(10, 0,str(self.h)+"x"+str(self.w), curses.A_NORMAL)
		self.screen.refresh()

	def initCursesOptions(self):
		curses.start_color()
		curses.use_default_colors()
		curses.noecho()
		curses.cbreak()
		curses.curs_set(False)
		curses.init_pair(2, curses.COLOR_BLACK, curses.COLOR_BLUE)
		curses.init_pair(3, curses.COLOR_BLUE, curses.COLOR_BLACK)
