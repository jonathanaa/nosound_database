from ctypes import cdll
import ctypes 
import sys
lib = cdll.LoadLibrary('D:\\xampp\\htdocs\\nosound_database\\interface\\libfoo2.so')#路徑要注意!!!!!!!!
url = sys.argv[1] #即為獲取到的PHP傳入python的入口引數
title=sys.argv[2]
content=sys.argv[3]
viewcount=sys.argv[4]
res=sys.argv[5]
duration=sys.argv[6]
lib.new_python(ctypes.c_char_p(url.encode('utf-8')),ctypes.c_char_p(title.encode('utf-8')),ctypes.c_char_p(content.encode('utf-8')),ctypes.c_char_p(viewcount.encode('utf-8')),ctypes.c_char_p(res.encode('utf-8')),ctypes.c_char_p(duration.encode('utf-8')))