from ctypes import cdll
import ctypes 
import sys
lib = cdll.LoadLibrary('D:\\xampp\\htdocs\\nosound_database\\interface\\libfoo2.so')#路徑要注意!!!!!!!!
search = sys.argv[1] #即為獲取到的PHP傳入python的入口引數
data=sys.argv[2:]
datastr=' '.join(data)
if search=='url':#新增
	lib.search_urls(ctypes.c_char_p(datastr.encode('utf-8')))
if search=='title':#搜尋
	lib.search_titles(ctypes.c_char_p(datastr.encode('utf-8')))
if search=='content':#刪除
	lib.search_contents(ctypes.c_char_p(datastr.encode('utf-8')))
if search=='viewcount':#刪除
	lib.search_viewcounts(ctypes.c_char_p(datastr.encode('utf-8')))
if search=='res':#刪除
	lib.search_ress(ctypes.c_char_p(datastr.encode('utf-8')))
if search=='duration':#刪除
	lib.search_durations(ctypes.c_char_p(datastr.encode('utf-8')))