  При реализации синхронизации процессов использовать функции ожидания сигнального состояния объекта только с
равным нулю или бесконечности интервалом ожидания. Каждый отдельный процесс открывать в отдельном
консольном окне. Использовать функцию WaitForMultipleObject для ожидания одного из группы событий.
  ПЕРЕДАЧА СООБЩЕНИЙ : Отправить сообщение, например, А или В от одного процесса другому, в данном задании
означает : создаем события соответсвующие сообщениям А и В. Затем вводится одно из сообщений (А или В) с
консоли в одном процессе и устанавливается соответсвующее событие в сигнальное состояние. В другом процессе
ожидается одно из событии и выводится на консоль соответствующее сообщение..
  АКТИВНЫЙ процесс- процесс, который может отправить сообщение, введённое с консоли и получить сообщение.
  
  Написать программы для консольного процесса Administrator и консольных процессов Reader и Writer. Для
моделирования передачи сообщений ввести специальные события(c автоматическим сбросом), которые
обозначают сообщение “A”, сообщение “B” и конец сеанса для процессов Reader и Writer.
Одновременно отправлять сообщения могут только ОДИН АКТИВНЫЙ процесс Writer (использовать мьютекс) и
принимать и отправлять ДВА АКТИВНЫХ процесса Reader(использовать семафор), передача остальных сообщений
от других процессов должна временно блокироваться (находиться в режиме ожидания);

  Процесс Administrator:
1. Инициализация объектов синхронизации;
2. запрашивает у пользователя количество процессов Reader и Writer, которые он должен запустить;
3. запрашивает у пользователя кол-во отправленных сообщений для процесса Writer и кол-во принятых
сообщений для процесса Reader (общее количество отправленных Writer и принятых Reader сообщений
должно совпадать);
4. запускает заданное количество процессов Reader и Writer;
5. принимает от каждого процесса Reader сообщение и выводит его на консоль в одной строке.
6. принимает от каждого процесса Reader и Writer сообщение о завершении сеанса и выводит его на консоль
в одной строке.
7. завершает свою работу.
  Процесс Writer:
1. синхронизировать работу процессов Writer с помощью мьютекса
2. передачу сообщений реализовать с помощью событий
3. запрашивает с консоли сообщения( “A” или “B” ) , и передает их (по одному) процессу Reader;
4. передает сообщение о завершении сеанса процессу Administrator;
5. завершает свою работу.
  Процесс Reader:
1. синхронизировать работу процессов Reader с помощью семафора
2. передачу сообщений реализовать с помощью событий
3. принимает сообщение от процесса Writer;
4. выводит на консоль сообщение “A” или “B” ;
5. передает сообщение от Writer - процессу Administrator;
6. передает сообщение о завершении сеанса процессу Administrator;
7. завершает свою работу. 
