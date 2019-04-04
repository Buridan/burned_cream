from os import listdir, getcwd, system, chdir, path, listdir
from Menu import Menu, ParentMenu, ChildMenu, CurrentMenu
from screen import ScreenEnvironment

class Panel():
	def __init__(self,screen_environment):
		self.width = 60
		self.menu_index = -1
		self.menu_list = []
		self.scr_env = screen_environment
		self.addMenus(getcwd())
	def addMenus(self, path):
		self.menu_index+=1
		self.menu_list.append(ParentMenu(path+"/../",self.scr_env.screen, 0))
		self.menu_index+=1
		self.menu_list.append(CurrentMenu(path,self.scr_env.screen, self.getCenteredBlock(self.width)))
		self.menu_list[0].searchChildItem(path)
		#self.menu_index+=1
		#self.menu_list.append(ChildMenu(path,self.scr_env.screen,self.alignRight(self.width)))
	def getFocusedMenu(self):
		return self.menu_list[1]
	def display(self):
		for f in range(self.menu_index):
			self.menu_list[f].display()
	def goLeft(self):
		self.menu_list=[]
		self.menu_index = 1
		chdir("..")
		self.addMenus(getcwd())
		#self.scr_env.screen.clear()
		#for f in range(self.menu_index):
		#	self.menu_list[f].moveOut()
		#self.display()
	def goRight(self):
		self.menu_list=[]
		self.menu_index = 1
		chdir(getcwd() + self.menu_list[1].moveIn())
		self.addMenus(getcwd())
	def getCenteredBlock(self,width):
		return (self.scr_env.w>>1)-(width>>1)
	def alignRight(self,width):
		return self.scr_env.w - self.width
