
<html>
    <head>SIUU</head>
    <body>
        <?php
            header("Location: ../add_forms/redirect.html");
            // create connection
            $conn = mysqli_connect("localhost", "group30", "apachewhich", "group30");
            if (mysqli_connect_errno()) {
                echo "Failed to connect to DB!";
                exit();
            }
            if(isset($_POST["submit"])){
                $f_name = $_POST["f_name"];
                $email = $_POST["email"];
                $password = $_POST["password"];
                $d_name = $_POST["d_name"];
                $dob = $_POST["dob"];
                $result = mysqli_query($conn, "SELECT d_id FROM departments WHERE name='$d_name'");
                $row = $result->fetch_assoc();
                $d_id = $row["d_id"];
                

                $sql = "INSERT INTO person(full_name, email, dob) VALUES(
                    '$f_name', '$email', '$dob'
                    )";
                if(mysqli_query($conn, $sql)){
                    $sql = "SELECT id FROM person ORDER BY id DESC LIMIT 1;";
                    $result = mysqli_query($conn, $sql);
                    $ids = $result->fetch_row();
                    $id = $ids[0];
                    $sql = "INSERT INTO admins VALUES(
                        '$id', '$password', '$d_id'
                    )";  
                    if(mysqli_query($conn, $sql)){
                        $sql = "SELECT num_of_emps FROM departments WHERE d_id=$d_id;";
                        $result = mysqli_query($conn, $sql);
                        $num = $result->fetch_row();
                        $total = $num[0] + 1;
                        $sql = "UPDATE departments SET num_of_emps=$total WHERE d_id=$d_id";
                        if(mysqli_query($conn, $sql)){
                            echo "Record added successfully!";
                        }
                        else{
                            echo "Error inserting: " . mysqli_error($conn) . "<br>";
                        }
                    }
                    else{
                        echo "Error inserting: " . mysqli_error($conn) . "<br>";
                    }
                }else{
                    echo "Error inserting: " . mysqli_error($conn) . "<br>";
                }
            }
            $conn->close();
        ?>
    </body>
</html>
