from selenium import webdriver
from selenium.webdriver.common.keys import Keys

browser = webdriver.Firefox()

browser.get('http://www.baidu.com')
browser.get('http://www.baidu.com')
browser.get('http://www.baidu.com')
ource = browser.page_source
print ource
browser.quit()
