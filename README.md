# Сервер Mkolyadin.ru. Инструкции для запуска.

## Запуск веб-сервера:

cd src && make && ./server

## Запуск кластера Kubernetes:

minikube profile list (список кластеров)
minikube profile nodejs или apache (переключение для управления kubectl)

minikube start --profile nodejs --nodes 3 --force
kubectl get pods -A

Проброс портов из контейнеров внутрь кластера.
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080
kubectl expose deployment/php-apache --type="NodePort" --port 80

Проброс портов из кластера наружу.
while true; do kubectl port-forward --address 0.0.0.0 service/kubernetes-bootcamp 3491:8080; done
while true; do kubectl port-forward --address 0.0.0.0 service/php-apache 3492:80; done
(использовать цикл или править конфиг Cubelet - убрать отключение при неактивности)

## Запуск PostgreDB
sudo -u postgres postgres -h 0.0.0.0 -D /var/lib/pgsql/postgres-db

## Запуск Jenkins
cd /root/contrib/jenkins/quickstart-tutorials/
docker compose --profile maven up -d
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

## TODO
- Мониторинг инфраструктуры Zabbix.
- Отслеживание OpenTelemetry.
- Поисковый движок Elastic Search и стек ELK.
- Сервер Gitlab (удален из-за расхода ресурсов, требует 4 ядра, содержит много сервисов).


## Исправленные ошибки.
- Ошибки сервера: завершение и чистка процессов.
- Ошибки HTML-cтраниц: вёрстка, ошибки загружаемых ресурсов.
- Сетевые ошибки - роутер обрывал соединения при большой нагрузке (торренты, ERR_CONNECTION_RESET).
- Kubernetes, автоотключение пода при пробросе портов (idle timeout).