from bs4 import BeautifulSoup
import requests
import time
import serial
import datetime
#from os import system

#port where the arduino is located
puerto = 'COM4'

baudrate = 2000000
ser = serial.Serial(port=puerto, baudrate=baudrate)
ser.isOpen()
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'}
numberFollowedBy = 0

print("⚠️  Only with public accounts⚠️")
user = input("User name instagram: ")
try:
    while(True):
        
        response = requests.get(f"https://www.picuki.com/profile/{user}",headers=headers)
        html = response.content
        soup = BeautifulSoup(html, 'html.parser')
        username = soup.find('h1', class_= 'profile-name-top').get_text()
        name = soup.find('h2', class_= 'profile-name-bottom').get_text()
        followedBy = soup.find('span', class_= 'followed_by').get_text()
        follows = soup.find('span', class_= 'follows').get_text()

        if numberFollowedBy!=followedBy:
            numberFollowedBy = followedBy
            ser.write(f"{username} +{name} +{followedBy} +{follows} + -- ".encode())
            #system("cls")
            print(f"Send data {datetime.datetime.now()}")
        else:
            #system("cls")
            print(f"No Changes {datetime.datetime.now()}")
        
        time.sleep(180)
except:
    print("Error")