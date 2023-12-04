# -*- coding: utf-8 -*-
from flask import Flask, request, jsonify, render_template, redirect, url_for
import socket
import json
import threading
from concurrent.futures import ThreadPoolExecutor

app = Flask(__name__)

# Список для хранения статистики
click_statistics = []
statistics_lock = threading.Lock()  # Добавляем блокировку

def process_socket_data(data):
    try:
        json_data = json.loads(data)
        ip_address = json_data.get('ip_address')
        redirected_url = json_data.get('redirected_url')
        timestamp = json_data.get('timestamp')

        # Заблокируем доступ для других потоков при изменении данных
        with statistics_lock:
            click_statistics.append({
                'ip_address': ip_address,
                'redirected_url': redirected_url,
                'timestamp': timestamp
            })

        print(f"Received data from socket: {json_data}")
        db_server_ip = '127.0.0.1'
        db_server_port = 6379
        # Создаем сокет
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Устанавливаем соединение с сервером
        client_socket.connect((db_server_ip, db_server_port))

        # Создаем сообщение, которое будет отправлено серверу
        message = f"{ip_address} {redirected_url} from_collecting_statistics {timestamp}"

        # Отправляем сообщение на сервер
        client_socket.send(message.encode())

        # Закрываем соединение с сервером
        client_socket.close()

    except Exception as e:
        print(f"Error processing socket data: {e}")

def start_socket_listener():
    # Создаем сокет в отдельном потоке
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_ip = '127.0.0.1'
    server_port = 5005

    server_socket.bind((server_ip, server_port))
    server_socket.listen(5)

    print(f"Socket listener started on {server_ip}:{server_port}")

    while True:
        client_socket, client_address = server_socket.accept()
        data = client_socket.recv(1024).decode()

        # Обработка данных из сокета в отдельном потоке
        with ThreadPoolExecutor() as executor:
            executor.submit(process_socket_data, data)

        client_socket.close()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/show_report')
def show_report():
    try:
        # Получение данных из базы данных
        report_entries = json.loads(db_response)

        # Отображение отчета на странице
        return render_template('report.html', report_entries=report_entries)
    
    except Exception as e:
        # Возвращаем ответ с ошибкой
        return jsonify({'success': False, 'message': f'Error processing database response: {str(e)}'})

@app.route('/report', methods=['POST'])
def generate_report():
    global db_response  # Объявление, что используется глобальная переменная

    if request.method == 'POST':
        dimensions = " ".join(request.json.get('Dimensions', []))
        
        db_server_ip = '127.0.0.1'
        db_server_port = 6379
        # Создаем сокет
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Устанавливаем соединение с сервером
        client_socket.connect((db_server_ip, db_server_port))

        # Формируем строку для отправки на сервер
        message = f"Dimensions {dimensions}"

        # Отправляем строку на сервер
        client_socket.send(message.encode())

        # Теперь принимаем данные от базы данных
        db_response = client_socket.recv(4096).decode()

        # Закрываем соединение с сервером
        client_socket.close()

        # Возвращаем данные в виде JSON-ответа
        return jsonify({'success': True, 'data': db_response})
        

if __name__ == '__main__':
    # Запуск сокета в отдельном потоке
    socket_thread = threading.Thread(target=start_socket_listener)
    socket_thread.start()

    # Запуск Flask в главном потоке
    app.run(debug=True, port=5001, use_reloader=False)



