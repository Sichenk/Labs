# -*- coding: utf-8 -*-
from flask import Flask, render_template, request, redirect
import pyshorteners as short
import socket

app = Flask(__name__)

# Создаем объект для сокращения ссылок
s = short.Shortener()

# Словарь для хранения сокращенных ссылок
shortened_links = {}

# IP-адрес и порт сервера
server_ip = '127.0.0.1'
server_port = 6379
# cd C:\Prakt_3\Prakt_3
# python Prakt_3.py
def send_data_to_server(short_link, original_link):
    # Создаем сокет
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Устанавливаем соединение с сервером
    client_socket.connect((server_ip, server_port))

    # Создаем сообщение, которое будет отправлено серверу
    message = f"Prakt_2 --file C:\links.txt --query HSET {original_link} {short_link}"

    # Отправляем сообщение на сервер
    client_socket.send(message.encode())

    # Закрываем соединение с сервером
    client_socket.close()

    return "The data has been successfully sent to the server."

@app.route('/')
def Decor():
    return render_template('index.html')

@app.route('/shorten', methods=['POST'])
def shorten_link():
    if request.method == 'POST':
        original_link = request.form.get('original_link')

        # Сокращаем исходную ссылку
        shortened_link = s.tinyurl.short(original_link)

        # Сохраняем сокращенную ссылку в словаре
        shortened_links[shortened_link] = original_link

        # Отправляем данные на другой сервер через сокет
        send_data_to_server(shortened_link, original_link)

        return f"Shortened link: <a href='{shortened_link}'>{shortened_link}</a>"

@app.route('/<short_link>')
def redirect_to_original(short_link):
    # Перенаправляем пользователя на исходную страницу
    original_link = shortened_links.get(short_link)
    if original_link:
        return redirect(original_link)
    else:
        return "Link not found!"

if __name__ == '__main__':
    app.run(debug=True)
