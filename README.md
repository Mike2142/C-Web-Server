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

## Запуск репозитория Gitlab (https://docs.gitlab.com/omnibus/installation/):

В обычной ситуации, сервер GitLab запускается автоматически.

Первичный запуск:

- Скачать RPM пакет (потребуется VPN):
    - Enterprise https://packages.gitlab.com/gitlab/gitlab-ee
    - Community https://packages.gitlab.com/gitlab/gitlab-ce
- Прописать адрес сервера (192.168.0.158).
    - Строка external_url in /etc/gitlab/gitlab.rb
- Настроить корневого пользователя.

sudo gitlab-ctl reconfigure

## Конструктор Telegram-ботов:
https://cp.puzzlebot.top/home

## Настройки роутера:

Внешний адрес роутера: http://46.38.107.141/
Внутренний адре: http://192.168.0.1/

Доп. настройки -> Переадресация NAT -> Виртуальные серверы
2	Mkolyadin.ru	80	192.168.0.158	3490	TCP		
3	Hello Minikube	3491	192.168.0.158	3491	TCP		
4	GitLab	3492	192.168.0.158	80	TCP
