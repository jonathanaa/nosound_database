from ctypes import cdll
import ctypes 
import sys
lib = cdll.LoadLibrary('D:\\xampp\\htdocs\\nosound_database\\interface\\libfoo2.so')#路徑要注意!!!!!!!!
delete = sys.argv[1] #即為獲取到的PHP傳入python的入口引數
data=sys.argv[2:]
datastr=' '.join(data)
if delete=='url':#新增
	lib.delete_urls(ctypes.c_char_p(datastr.encode('utf-8')))
if delete=='title':#搜尋
	lib.delete_titles(ctypes.c_char_p(datastr.encode('utf-8')))
if delete=='content':#刪除
	lib.delete_contents(ctypes.c_char_p(datastr.encode('utf-8')))
if delete=='viewcount':#刪除
	lib.delete_viewcounts(ctypes.c_char_p(datastr.encode('utf-8')))
if delete=='res':#刪除
	lib.delete_ress(ctypes.c_char_p(datastr.encode('utf-8')))
if delete=='duration':#刪除
	lib.delete_durations(ctypes.c_char_p(datastr.encode('utf-8')))