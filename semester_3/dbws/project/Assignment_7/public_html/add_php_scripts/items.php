
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
                $item_name = $_POST["item_name"];
                $c_name = $_POST["c_name"];
                $quantity = $_POST["quantity"];
                $is_consumable = $_POST["consumable"];
                $result = mysqli_query($conn,"SELECT c_id FROM categories WHERE c_name='$c_name'");
                $row = $result->fetch_assoc();
                $c_id = $row["c_id"];    

                if(strcmp($is_consumable, "Yes") == 0){               
                $sql = "INSERT INTO items(item_name, isConsumable, quantity, c_id) VALUES(
                    '$item_name', 1, '$quantity', '$c_id'
                    )";
                }else{
                    $sql = "INSERT INTO items(item_name, isConsumable, quantity, c_id) VALUES(
                        '$item_name', 0, '$quantity', '$c_id'
                        )";
                }
                if(mysqli_query($conn, $sql)){
                    echo "Record Added Successfully.";
                    $sql = "SELECT num_of_items FROM categories WHERE c_id=$c_id";
                    $result = mysqli_query($conn, $sql);
                    $row = $result->fetch_assoc();
                    $num = $row["num_of_items"];
                    $new_num = $num+1;
                    $sql = "UPDATE categories SET num_of_items=$new_num WHERE c_id=$c_id";
                    mysqli_query($conn,$sql);

                }else{
                    echo "Error inserting: " . mysqli_error($conn) . "<br>";
                }
            }
            $conn->close();
        ?>
    </body>
</html>
