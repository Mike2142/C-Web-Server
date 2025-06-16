# C Server Mkolyadin.ru

## Запуск веб-сервера:

cd src && make && ./server

## Запуск кластера Kubernetes:

minikube profile list (список кластеров)
minikube profile c2 (переключение для управления kubectl)
minikube delete --profile c2 (если не запускается)

minikube start --profile c2 --nodes 3 --force
kubectl get pods -A

Проброс портов из контейнеров внутрь кластера.
kubectl expose deployment/kubernetes-bootcamp --type="NodePort" --port 8080
kubectl expose deployment/php-apache --type="NodePort" --port 80

Проброс портов из кластера наружу.
kubectl port-forward --address 0.0.0.0 service/kubernetes-bootcamp 3491:8080
kubectl port-forward --address 0.0.0.0 service/php-apache 3492:80

TODO: Вывод панели управления на сайт mkolyadin.ru (?).
Мониторинг и управление кластерами.
minikube dashboard



## Запуск репозитория Gitlab (https://docs.gitlab.com/omnibus/installation/):

sudo gitlab-ctl start

sudo gitlab-ctl stop

sudo gitlab-ctl restart

sudo gitlab-ctl restart sidekiq (запуск инд. компонентов)

sudo gitlab-ctl restart-except gitaly redis

В обычной ситуации, сервер GitLab запускается автоматически. Требуется 10-15 мин. для полного запуска (доступно окно входа).

Первичный запуск:

- Скачать RPM пакет (потребуется VPN):
    - Enterprise https://packages.gitlab.com/gitlab/gitlab-ee
    - Community https://packages.gitlab.com/gitlab/gitlab-ce
- Прописать адрес сервера (192.168.0.158).
    - Строка external_url in /etc/gitlab/gitlab.rb
- Настроить корневого пользователя.

sudo gitlab-ctl reconfigure

TODO: Добавить описание компонентов.

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
    - Настройка машин после создания.
      - Пароль для guest, ssh-доступ с паролем (/etc/ssh/sshd_config AllowPasswordAuthentication).

Копирование конфигов для репозитория:
    - cp ../terraform/main.tf ./terraform-example/
    - cp ../terraform/meta.txt ./terraform-example/

Токен для облака (YC_Token) нужно обновлять каждый день (делать перезапуск терминала, .bash_profile).

TODO: 
- Пароль для гостевых аккаунтов:
  - meta.txt/lock_passwd: false 
  - meta.txt/passwd: <хэш пароля SHA-512>.

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


## Исправленные ошибки.
- Ошибки сервера: завершение и чистка процессов.
- Ошибки HTML-cтраниц: вёрстка, ошибки загружаемых ресурсов.
- Сетевые ошибки - роутер обрывал соединения при большой нагрузке (торренты, ERR_CONNECTION_RESET).