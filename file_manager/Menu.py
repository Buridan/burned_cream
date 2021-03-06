import curses
from os import curdir, listdir, getcwd, system, chdir, path, listdir
from os.path import isfile

class Menu:
	def __init__(self,menuName,screen,positionX):
		self.name = menuName
		self.x = positionX
		self.nextLine = 1
		self.menu_index = 0
		self.menu_array = []
		self.screen = screen
		for f in listdir(self.name):
			self.addItem(f)
		self.display()
	def addItem(self, item_name):
		self.menu_array.append(MenuItem(item_name, self.nextLine))
		self.nextLine +=1
		self.menu_array[0].setSelected(True)
	def display(self):
		self.screen.addstr(0, self.x, self.name, curses.A_NORMAL)
		for item in self.menu_array:
			self.screen.addstr(item.getLine(), self.x , item.getName().ljust(60),
							curses.color_pair(2) if item.isSelected() else curses.A_NORMAL)
	def nextItem(self):
		if self.menu_index != len(self.menu_array)-1:
			self.menu_array[self.menu_index].setSelected(False)	
			self.menu_index += 1
			self.menu_array[self.menu_index].setSelected(True)	
			self.display()
	def previousItem(self):
		if self.menu_index != 0:
			self.menu_array[self.menu_index].setSelected(False)	
			self.menu_index -= 1
			self.menu_array[self.menu_index].setSelected(True)	
			self.display()
	def moveOut(self):
		self.setName(getcwd()+"../")
		self.menu_array = []
		self.menu_index = 0
		self.nextLine = 1
		for f in listdir("."):
			self.addItem(f)
		self.display()
	def moveIn(self):
		self.screen.clear()
		if self.menu_array[self.menu_index].type :
			self.menu_array[self.menu_index].execute()
			return ""
		else:
			self.setName(getcwd())
			self.menu_array = []
			self.menu_index = 0
			self.nextLine = 1
			for f in listdir("."):
				self.addItem(f)
			self.display()
			return getcwd() + self.menu_array[self.menu_index].name
	def setName(self,newName):
		self.name = newName
	def setPosition(self,x):
		self.x = x
	def upDir(self):
		self.name+="/../"
	def execute(self):
		self.menu_array[menu_index].execute()
	def searchChildItem(self,path):
		for item in self.menu_array:
			if item.name == path:
				item.setSelected(False)
				


class CurrentMenu(Menu):
	def __init__(self,menuName,screen,positionX):
		Menu.__init__(self,menuName,screen,positionX)
class ParentMenu(Menu):
	def __init__(self,menuName,screen,positionX):
		Menu.__init__(self,menuName,screen,positionX)
		chdir(self.name + "/../")
		self.name = getcwd()
	def addItem(self, item_name):
		self.menu_array.append(MenuItem(item_name, self.nextLine))
		self.nextLine +=1
		self.menu_array[0].setSelected(True)
class ChildMenu(Menu):
	def __init__(self,menuName,screen,positionX):
		Menu.__init__(self,menuName,screen,positionX)

class MenuItem():
	def __init__(self, name, line):
		self.name = name
		self.line = line
		self.selected = False
		self.type = path.isfile(self.name)
	def execute(self):
		if self.type :
			system("vim " + self.name)
		else: chdir(str("./"+self.name))
	def getName(self):
		return self.name
	def setSelected(self,toggle):
		self.selected = toggle
	def isSelected(self):
		return self.selected
	def getLine(self):
		return self.line
