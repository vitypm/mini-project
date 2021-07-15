use laba2;
/* Задание 1 */
delimiter //
drop procedure IF EXISTS task1; //
create procedure task1()
	begin
        declare id int default 0;
        declare count_orders int default 0;
        declare sum_price int default 0;
        declare proverka int default 0;
        declare done int default 0;

        declare cur cursor for select clients.id from clients;

        DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done=1; 
	-- Если доступных строк больше нет, возникает условие «Нет данных» со значением SQLSTATE '02000', чтобы выйти в дальнейшем из цикла (Можно использовать LOOP, WHILE ...)

		/* Метод который сообщает языку sql, открываем участок памяти который будет обрабатыватся*/
        Open cur;	
		
        drop temporary table if exists client_info;
        create temporary table client_info(id int primary key auto_increment, id_client int, count_orders int, totally_price int);
		
        While done = 0 do 
			Fetch cur into id;
			/*
				Это вроде что-то массива, который беребирает каждую строку, строка не должна быть пустой, 
					- Недостаточная чувствительность: сервер может или не может делать копию своей таблицы результатов.
					- Только чтение: не обновляется
					- Не прокручивается: можно перемещаться только в одном направлении и нельзя пропускать строки.
			*/
			
            select count(orders.id), sum(price) from orders 
				join contracts on (contracts.id = orders.contractId) 
				join clients on (clients.id = contracts.cliendId) 
					where clients.id = id into count_orders , sum_price; # Добавляем в переменные, информацию

            select id into proverka from clients where clients.id = id + 1; 

            if (proverka = 0) then  
				set done = 1;
			end if;

            insert into client_info (id_client, count_orders, totally_price) values (id, count_orders, sum_price);
			
		End while;
				select 
					id_client as 'Номер клиента', 
					count_orders as 'Количество заказов', 
					totally_price as 'Сумма всех заказов' from client_info;	#Вывод добавленных данных
        Close cur;
	End;
    //
delimiter ;
call task1();



use laba2;

/* Задание 2 */
/* Создаем таблицу, куда будем записывать весь результат. */
drop table IF EXISTS statistika_po_tovaram; 
create table statistika_po_tovaram (id int primary key auto_increment, id_tovar int, tovar_name varchar(255), amount_of_items int, date date, month int, year int);
drop function IF EXISTS text_month; 
drop function IF EXISTS test; 

delimiter //
create function text_month(a int)
	returns char
	no sql
    begin
		declare month varchar(255) default '';
		if(a = 1) then set month ='Январь'; end if;
        if(a = 2) then set month ='Февраль'; end if;
        if(a = 3) then set month ='Март'; end if;
        if(a = 4) then set month ='Апрель'; end if;
        if(a = 5) then set month ='Май'; end if;
        if(a = 6) then set month ='Июнь'; end if;
        if(a = 7) then set month ='Июль'; end if;
        if(a = 8) then set month ='Август'; end if;
        if(a = 9) then set month ='Сентябрь'; end if;
        if(a = 10) then set month ='Октябрь'; end if;
        if(a = 11) then set month ='Ноябрь'; end if;
        if(a = 12) then set month ='Декабр'; end if;
        return cast(month as unsigned);
	End; //

drop procedure IF EXISTS test; //
create function test(tovar_id int, c_date date)
	returns int
    no sql
	begin
		declare nomer_tovara int default 0;
        declare result int default 9;
		/*Проверка */
		select id_tovar from statistika_po_tovaram 
			where (statistika_po_tovaram.id_tovar = tovar_id) 
					and statistika_po_tovaram.month = month(c_date) 
					and statistika_po_tovaram.year = year(c_date) 
						limit 1
						into nomer_tovara;

		if (nomer_tovara = 0) then 
          set result = 1;
          return cast(result as unsigned);
		Else
        set result = 0;
		  return cast(result as unsigned);
		End if;
                /*----------- */
	End; //

drop procedure IF EXISTS task2_calculate; //
create procedure task2_calculate(tovar_id int, c_date date)
	begin
		declare done int default 0;
        declare nomer_tovara int default 0;
        declare name_tovar varchar(255) default '';
        declare date_ date;
        declare amount_of_tovar int default 0;
        declare no_insert int default 0;
        
        declare id_tovar_result int default 0;
        declare tovar_name_result varchar(255) default '';
        declare amount_result int default 0;
        declare month_result int;
        declare year_result int;
		declare cur2 cursor for select items.inventory_code, items.item_title, more_items.amount_of_item, orders.start_date from orders 
										join more_items on (more_items.orderId = orders.id)
										join items on (more_items.itemId = items.inventory_code)
											order by orders.id;

		DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done=1;
			Open cur2;
            /* Проверка обработали ли мы уже данные по определенному товару, месяцу и году */
            if (test(tovar_id, c_date) = 0) then set done = 1; set no_insert = 1; end if;
            /*----------------------------------------------------------------------------- */
            drop temporary table if exists temp_table;
			create temporary table temp_table (id int primary key auto_increment, id_tovar int, tovar_name varchar(255), amount_of_items int, date date);

			While done = 0 do
				Fetch cur2 into nomer_tovara, name_tovar, amount_of_tovar, date_;

				if((nomer_tovara = tovar_id) and (month(date_) = month(c_date)) and (year(date_) = year(c_date)) ) then
					select 'Условие работает';
					insert into temp_table(id_tovar, tovar_name, amount_of_items, date) values (nomer_tovara, name_tovar, amount_of_tovar, date_);
				End if;
			End while;
            if (no_insert = 0) then
				select id_tovar, tovar_name, sum(amount_of_items), month(date), year(date), date from temp_table 
					group by id_tovar into id_tovar_result, tovar_name_result, amount_result, month_result, year_result, date_;
				insert into statistika_po_tovaram (id_tovar, tovar_name, amount_of_items, date, month, year) 
					values (id_tovar_result, tovar_name_result, amount_result, date_, month_result, year_result );
            End if;
            truncate table temp_table;
	End; //
drop procedure IF EXISTS task2; //
create procedure task2()
	begin
		declare id_tovar int default 0;
        declare proverka int default 0;
        declare date_ date;
        declare done int default 0;
        declare cur1 cursor for select items.inventory_code, orders.start_date from orders 
				join more_items on (more_items.orderId = orders.id)																	   
				join items on (more_items.itemId = items.inventory_code);
        DECLARE CONTINUE HANDLER FOR SQLSTATE '02000' SET done=1;
        truncate table statistika_po_tovaram;
        Open cur1;
        While done = 0 do
			Fetch cur1 into id_tovar, date_;
            call task2_calculate(id_tovar, date_);
		End while;
        select statistika_po_tovaram.id_tovar as 'Номер товара', statistika_po_tovaram.tovar_name as 'Название товара', amount_of_items as 'Количество товара', date as 'Дата', month as 'Месяц', year as 'Год' from statistika_po_tovaram;    
	End //
    
delimiter ;
call task2();
select id_tovar as 'Номер товара', tovar_name as 'Название товара', amount_of_items as 'Количество товара', date as 'Дата', month as 'Месяц', year as 'Год' from statistika_po_tovaram; 





