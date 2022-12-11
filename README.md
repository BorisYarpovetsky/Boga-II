Boga-II

Работает на Windows

Для запуска на Windows нужно прописть команду .\makefile 

![image](https://user-images.githubusercontent.com/94048839/206925215-665b5b42-bbfe-4251-965d-274418ac61f1.png)

Работает на Linux

Работает в Web

Для запуска на Web нужно установить emsdk и ввести команды:
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install latest
./emsdk activate latest
./emsdk_env.sh
./emsdk && http-server

![image](https://user-images.githubusercontent.com/94048839/206925586-31d07333-b587-454c-bf61-fa0ba1dc01c2.png)
