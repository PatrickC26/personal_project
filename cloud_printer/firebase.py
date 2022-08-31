import requests

url = "https://sloth-pi-printer-default-rtdb.firebaseio.com/"
key = ".json?auth=m6BOgzqmGfeEg0cIFZrUjqkiuyWaDmqybidJy5OY"
timeURL = "http://worldtimeapi.org/api/timezone/Asia/Taipei"
def firebaseGET(path) :
    conn = requests.get(url + path + key)
    return conn.text[1:-1]

def timeGET() :
    conn = requests.get(timeURL)
    nowS = conn.text
    nowS = nowS[nowS.index("datetime")+11 : nowS.index("+08:00\"")]
    nowS = nowS[0 : nowS.index(".")].replace("T"," ")
    return nowS

def firebasePUT(path, data) :
    path_slash = 0
    if ("/" in path) :
        path_slash = path.rindex("/")
    send = {path[path_slash : ] : data}
    conn = requests.patch(url = url + path[0 : path_slash] + key, json = send)

