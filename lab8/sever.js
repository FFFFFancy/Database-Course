//express_demo.js
var express = require('express');
var sql = require('mssql');
let bodyParser=require('body-parser');

var app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use("/*", function(request, response, next) {
    response.header("Access-Control-Allow-Origin", "*");
    response.header("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
    response.header("Access-Control-Allow-Methods", "PUT,POST,GET,DELETE,OPTIONS");
    response.header("Access-Control-Allow-Credentials", true); //可以带cookies
    response.header("X-Powered-By", 'Express');
    if (request.method == 'OPTIONS') {
      response.sendStatus(200);
    } else {
      next();
    }
});

// DB configuration
var dbConfig = {
  user: 'sa',
  password: 'sa1234',
  server: 'localhost',
  database: 'JY',
  port: 1433,
  options:{
      trustServerCertificate:true
  }
};

var conn = new sql.ConnectionPool(dbConfig);

app.get('/book/list', function (req, res) {
    var req = new sql.Request(conn);
    conn.connect(function (err) {
        if (err) {
            console.log(err);
            return;
        }
        // 查询 book 表
        req.query("SELECT * FROM book", function (err, recordset) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                console.log(recordset);
                res.send(recordset);
            }
            conn.close();
        });
    });
    
    // res.send('Hello World');
})

app.get('/book/search', function (request, response) {
    var req = new sql.Request(conn);
    let name1 = request.query.name;
    console.log(name1);
    conn.connect(function (err) {
        if (err) {
            console.log(err);
            return;
        }
        // 查询 book 表
        req.query(`SELECT * FROM book where book_name = '${name1}'` , function (err, recordset) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                console.log(recordset);
                response.send(recordset);
            }
            conn.close();
        });
    });
})

app.post('/book/upload', function (request, response) {
    console.log('收到post请求')
    var req = new sql.Request(conn);
    let newbook = request.body;
    //console.log(newbook);
    let _id = newbook.book_id;
    let _name = newbook.book_name;
    let _isbn = newbook.book_isbn;
    let _author = newbook.book_author;
    let _publisher = newbook.book_publisher;
    let _price = newbook.book_price;
    let _interviews = newbook.interview_times;

    conn.connect(function (err) {
        if (err) {
            console.log(err);
            return;
        }
        // 上传图书信息到 book 表
        req.query(`insert into book values('${_id}','${_name}','${_isbn}','${_author}','${_publisher}','${_price}','${_interviews}')` , function (err, recordset) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                let res = {};
                res['state'] = true;
                res['message'] = "Upload Succeed!";
                console.log('添加图书成功');
                response.send(res);
            }
            conn.close();
        });
    });
})

app.put('/book/change', function (request, response) {
    console.log('收到put请求')
    var req = new sql.Request(conn);

    let target_id = request.query.book_id;
    console.log(target_id);

    let newbook = request.body;
    //console.log(newbook);
    let _name = newbook.book_name;
    let _isbn = newbook.book_isbn;
    let _author = newbook.book_author;
    let _publisher = newbook.book_publisher;
    let _price = newbook.book_price;
    let _interviews = newbook.interview_times;

    conn.connect(function (err) {
        if (err) {
            console.log(err);
            return;
        }
        // 更新图书信息到 book 表
        req.query(`update book set  book_name='${_name}',
                                    book_isbn='${_isbn}',
                                    book_author='${_author}',
                                    book_publisher='${_publisher}',
                                    book_price='${_price}',
                                    interview_times='${_interviews}'
                                    where book_id='${target_id}'`,
                                    function (err, recordset) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                let res = {};
                res['state'] = true;
                res['message'] = "Update Succeed!";
                console.log('更新成功');
                response.send(res);
            }
            conn.close();
        });
    });
})

app.delete('/book/target', function (request, response) {
    console.log("收到delete请求")
    var req = new sql.Request(conn);
    let target = request.query;
    console.log(target);
    let _id = target.book_id;
    console.log(_id);

    conn.connect(function (err) {
        if (err) {
            console.log(err);
            return;
        }
        // 依据 book_id 删除 book 表相关图书信息
        req.query(`delete FROM book where book_id = '${_id}'` , function (err, recordset) {
            if (err) {
                console.log(err);
                return;
            }
            else {
                let res = {};
                res['state'] = true;
                res['message'] = "Delete Succeed!";
                console.log('删除图书信息成功');
                response.send(res);
            }
            conn.close();
        });
    });
})

var server = app.listen(8081, function () { 
  console.log("应用实例，访问地址为localhost:8081");
})