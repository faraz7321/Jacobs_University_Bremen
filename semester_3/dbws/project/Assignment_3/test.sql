CREATE TABLE person
(
    full_name varchar(255),
    email varchar(255),
    dob date,
    id int AUTO_INCREMENT,
    PRIMARY KEY(id)
);

CREATE TABLE departments
(
    d_id int AUTO_INCREMENT,
    num_of_emps int,
    PRIMARY KEY(d_id)
);

CREATE TABLE admins
(
    id int,
    pass_word varchar(255),
    d_id int,
    PRIMARY KEY(id),
    FOREIGN KEY(id) REFERENCES person,
    FOREIGN KEY(d_id) REFERENCES departments
);
CREATE TABLE employees
(
    id int NOT NULL,
    d_id int,
    pass_word varchar(255),
    PRIMARY KEY(id),
    FOREIGN KEY(id) REFERENCES person,
    FOREIGN KEY(d_id) REFERENCES departments
);



CREATE TABLE items
(
    item_name varchar(255),
    isConsumable bool,
    barcode int,
    quantity int,
    category varchar(255),
    PRIMARY KEY(barcode)
);
CREATE TABLE requests
(
    r_id int,
    item varchar(255),
    quantity int,
    reqDate date,
    retDate date,
    PRIMARY KEY(r_id)
);
CREATE TABLE history
(
    r_id int,
    item varchar(255),
    quantity int,
    request_status varchar(255),
    reqDate date,
    retDate date,
    PRIMARY KEY(r_id)
);