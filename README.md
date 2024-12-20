# C Server

Запуск сервера:

cd src && make && ./server

Запуск  Kubernetes Minikube:

minikube delete
minikube start --force
kubectl get po -A

kubectl create deployment hello-minikube --image=kicbase/echo-server:1.0
kubectl expose deployment hello-minikube --type=NodePort --port=8080

kubectl port-forward --address 0.0.0.0 service/hello-minikube 3491:8080

Настройки роутера:

Доп. настройки -> Переадресация NAT -> Виртуальные серверы
2	Mkolyadin.ru	80	192.168.0.158	3490	TCP		
3	Hello Minikube	3491	192.168.0.158	3491	TCP		
