Написать программы двух консольных процессов Server и Client, которые обмениваются сообщениями по анонимному каналу. Создать наследуемые дескрипторы канала.
Одновременно сообщение может передаваться только одним из процессов.
  Процесс- Server, который выполняет следующие действия:
- Размер массива вводится с консоли. Тип массива: long
- Запрашивает число числа N и M (N < M ).
- Запускает процесс Client.
- Передает процессу-Client по анонимным каналам размер массива и числа N и M.
- Получает от процесса-Client по анонимным каналам элементы массива.
- Выводит переданную и полученную информацию по каналу на консоль.
- Закончить работу после нажатия клавиши - “Q”.
  Процесс- Client , который выполняет следующие действия.
- Генерирует элементы массива в диапазоне [N ,M] и передает их по анонимному каналу процессу Server.
- Выводит полученную и переданную информацию по каналу на консоль.
- Закончить работу после нажатия клавиши - “Q”.
- Заканчивает работу
