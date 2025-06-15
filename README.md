# C Server Mkolyadin.ru

## Запуск веб-сервера:

cd src && make && ./server

## Запуск кластера Kubernetes Minikube:

minikube start --force
minikube delete (если не запускается)
kubectl get po -A

kubectl create deployment hello-minikube --image=kicbase/echo-server:1.0
kubectl expose deployment hello-minikube --type=NodePort --port=8080

kubectl port-forward --address 0.0.0.0 service/hello-minikube 3491:8080
minikube stop

## Запуск репозитория Gitlab (https://docs.gitlab.com/omnibus/installation/):

В обычной ситуации, сервер GitLab запускается автоматически. Требуется 10-15 мин. для полного запуска (доступно окно входа).

Первичный запуск:

- Скачать RPM пакет (потребуется VPN):
    - Enterprise https://packages.gitlab.com/gitlab/gitlab-ee
    - Community https://packages.gitlab.com/gitlab/gitlab-ce
- Прописать адрес сервера (192.168.0.158).
    - Строка external_url in /etc/gitlab/gitlab.rb
- Настроить корневого пользователя.

sudo gitlab-ctl reconfigure

## Запуск PostgreDB
sudo -u postgres postgres -h 0.0.0.0 -D /var/lib/pgsql/postgres-db

## Запуск Jenkins
cd ~/contrib/jenkins/quickstart-tutorials/
docker compose --profile maven up -d
Кабинет Jenkins: 192.168.0.158:8081 admin, admin.

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

## Исправленные ошибки.
- Ошибки сервера: завершение и чистка процессов.
- Ошибки HTML-cтраниц: вёрстка, ошибки загружаемых ресурсов.
- Сетевые ошибки - роутер обрывал соединения при большой нагрузке (торренты, ERR_CONNECTION_RESET).