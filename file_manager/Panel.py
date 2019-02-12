from os import getcwd
from Menu import ParentMenu, ChildMenu, MainMenu
from screen import ScreenEnvironment

class Panel():
	def __init__(self,screen_environment):
		self.width = 20
		self.menu_index = -1
		self.menu_list = []
		self.scr_env = screen_environment
		self.addMenus(getcwd())
	def addMenus(self, path):
		self.addParentMenu(path+"/../",0)
		self.addMainMenu(path,((self.scr_env.w/2)-(self.width/2)))
		self.addChildMenu(path,self.scr_env.w - self.width)
	def addParentMenu(self, path,posX):
		self.menu_index+=1
		self.menu_list.append(ParentMenu(path,self.scr_env.screen, posX))
	def addMainMenu(self, path,posX):
		self.menu_index+=1
		self.menu_list.append(MainMenu(path,self.scr_env.screen, posX))
	def addChildMenu(self, path,posX):
		self.menu_index+=1
		self.menu_list.append(ChildMenu(path,self.scr_env.screen, posX))
	def getFocusedMenu(self):
		return self.menu_list[1]
	def display(self):
		for f in range(self.menu_index):
			self.menu_list[f].display()
	def goLeft(self):

		self.getFocusedMenu().setPosition(self.scr_env.w - self.width)
		self.display()
