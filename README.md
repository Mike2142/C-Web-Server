# Сервер Mkolyadin.ru. Инструкции для запуска.

## Запуск веб-сервера:

while true; do ./server; done

cd src && make && ./server

## Запуск прокси-сервера NGINX (TLS шифрование).
Генерация тестовых сертификатов.
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt

Конфиг NGINX
- Перенаправление HTTP на HTTPS.
- Пути для сертификатов (getssl).
nano /etc/nginx/conf.d/proxy.conf 

nginx -t
systemctl enable nginx

## Генерация TLS-сертификатов.
Обновление сертификата на 90 дней.
getssl -f mkolyadin.ru
systemctl reload nginx

Установка программы.
curl --silent https://raw.githubusercontent.com/srvrco/getssl/latest/getssl > getssl ; chmod 700 getssl
getssl
nano ~/.getssl/mkolyadin.ru/getssl.cfg

Задача для crontab
~/bin/renew_cert.sh 
sudo crontab -e
30 3 * * * /root/bin/renew_cert.sh > /var/log/getssl_renew.log 2>&1

## Запуск кластера Kubernetes:

minikube profile list (список кластеров)
minikube profile nodejs или apache (переключение для управления kubectl)

minikube start --profile nodejs --nodes 2 --force
minikube start --profile apache --nodes 2 --force
kubectl get pods -A

kubectl create deployment kubernetes-bootcamp --image=gcr.io/google-samples/kubernetes-bootcamp:v1
kubectl apply -f https://k8s.io/examples/application/php-apache.yaml

Проброс портов из контейнеров внутрь кластера.
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080

Проброс портов из кластера наружу.
while true; do kubectl port-forward --address 0.0.0.0 service/kubernetes-bootcamp 3491:8080; done
while true; do kubectl port-forward --address 0.0.0.0 service/php-apache 3492:80; done
(использовать цикл или править конфиг Cubelet - убрать отключение при неактивности)

Повторный запуск.
minikube profile list
minikube start --force
while true; do kubectl port-forward --address 0.0.0.0 service/php-apache 3492:80; done

## Запуск PostgreDB
sudo -u postgres postgres -h 0.0.0.0 -D /var/lib/pgsql/postgres-db

## Запуск Jenkins
cd /root/contrib/jenkins/quickstart-tutorials/
docker compose --profile maven up -d
docker compose --profile maven up
docker compose --profile maven down

Кабинет Jenkins: 192.168.0.158:8081

## Запуск Prometheus
cd /root/contrib/prometheus/prometheus-2.53.4.linux-amd64/
./prometheus --config.file=prometheus.yml --web.listen-address=:9091

## Terraform Yandex Cloud
Создание инфры:
    - Папка contrib/terraform/
    - terraform destroy -> validate -> fmt -> plan -> apply
    - Статус облака отображается в консоли Яндекса.

Токен для облака (YC_Token) нужно обновлять каждый день (делать перезапуск терминала, source .bash_profile).

## Телеграм-бот
Конструктор https://cp.puzzlebot.top/home
Настройки @botfather (запуск, остановка, и др.)

## Настройки роутера:

Внешний адрес роутера: http://46.38.107.141/
Внешний адрес кабинета: http://46.38.107.141:1031
Внутренний адрес кабинета: http://192.168.0.1/

Доп. настройки -> Переадресация NAT -> Виртуальные серверы
2	Mkolyadin.ru	80	192.168.0.158	3490	TCP		
3	Hello Minikube	3491	192.168.0.158	3491	TCP		
4	GitLab	3492	192.168.0.158	80	TCP		
5	PostgreDB	2715	192.168.0.158	5432	TCP
6	Jenkins	2717	192.168.0.158	8081	TCP or UDP
7	Prometheus	2718	192.168.0.158	9091	TCP or UDP

## TODO (?)
- Мониторинг инфраструктуры Zabbix.
- Отслеживание OpenTelemetry.
- Поисковый движок Elastic Search и стек ELK.
- Сервер Gitlab (удален из-за расхода ресурсов, требует 4 ядра, содержит много сервисов).


## Исправленные ошибки.
- Ошибки сервера: завершение и чистка процессов.
- Ошибки HTML-cтраниц: вёрстка, ошибки загружаемых ресурсов.
- Сетевые ошибки - роутер обрывал соединения при большой нагрузке (торренты, ERR_CONNECTION_RESET).
- Kubernetes, автоотключение пода при пробросе портов (idle timeout).