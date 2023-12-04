# -*- coding: cp1251 -*-
from flask import Flask, render_template, request, redirect
import datetime
import hashlib
import urllib.parse  # Импортируем библиотеку для кодирования URL
import socket

app = Flask(__name__)

# Словарь для хранения соответствия между исходными и сокращенными ссылками
shortened_links = {}

# IP-адрес и порт сервера
server_ip = '127.0.0.1'
server_port = 6379
# cd C:\Users\Никита Сильченко\Desktop\Прога\Prakt_4\Prakt_3\Prakt_3
# python Prakt_3.py
def send_data_to_server(short_link, original_link):
    # Создаем сокет
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Устанавливаем соединение с сервером
    client_socket.connect((server_ip, server_port))

    # Создаем сообщение, которое будет отправлено серверу
    message = f"{original_link} {short_link} from_link_shortener"

    # Отправляем сообщение на сервер
    client_socket.send(message.encode())

    # Закрываем соединение с сервером
    client_socket.close()

def shorten_link(original_link):
    # Генерируем уникальный хэш от исходной ссылки
    hash_object = hashlib.sha256(original_link.encode())
    hash_value = hash_object.hexdigest()[:8]  # Используем первые 8 символов хэша

    # Формируем сокращенную ссылку
    shortened_link = f"http://localhost:5000/{urllib.parse.quote(hash_value)}"

    # Сохраняем соответствие в словаре
    shortened_links[urllib.parse.quote(hash_value)] = original_link
    
    # Отправляем данные на другой сервер через сокет
    send_data_to_server(shortened_link, original_link)

    return shortened_link

def send_data_to_stats_service(ip_address, redirected_url, timestamp):
    # Создаем сокет
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # IP-адрес и порт сервера статистики
    stats_server_ip = '127.0.0.1'
    stats_server_port = 5005

    try:
        # Устанавливаем соединение с сервером статистики
        client_socket.connect((stats_server_ip, stats_server_port))

        # Создаем сообщение, которое будет отправлено серверу статистики
        message = f"{{\"ip_address\": \"{ip_address}\", \"redirected_url\": \"{redirected_url}\", \"timestamp\": \"{timestamp}\"}}"
        
        # Отправляем сообщение на сервер статистики
        client_socket.send(message.encode())

    except Exception as e:
        print(f"Error sending data to stats service: {e}")

    finally:
        # Закрываем соединение с сервером статистики
        client_socket.close()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/shorten', methods=['POST'])
def shorten():
    if request.method == 'POST':
        original_link = request.form.get('original_link')

        # Сокращаем исходную ссылку
        shortened_link = shorten_link(original_link)

        return f"Shortened link: <a href='{shortened_link}'>{shortened_link}</a>"

@app.route('/<short_link>')
def redirect_to_original(short_link):
    # Перенаправляем пользователя на исходную страницу
    original_link = shortened_links.get(short_link)
    if original_link:
        # Получаем данные для отправки на сервис статистики
        ip_address = request.remote_addr
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        # Отправляем данные на сервер статистики
        send_data_to_stats_service(ip_address, original_link, timestamp)

        return redirect(original_link)
    else:
        return "Link not found!"

if __name__ == '__main__':
    app.run(debug=True, port=5000)


