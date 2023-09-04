<?php 
session_start(); 
include "connection.php";
if (isset($_POST['myusername']) && isset($_POST['mypassword'])) {
    function validate($data){
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }
    $uname = validate($_POST['myusername']);
    $pass = validate($_POST['mypassword']);
    if (empty($uname)) {
        header("Location: index.php?error=User Name is required");
        exit();
    }else if(empty($pass)){
        header("Location: index.php?error=Password is required");
        exit();

    }else{

        //$sql = "SELECT * FROM users WHERE user_name='$uname' AND password='$pass'";
        $sql ="select * from admins A inner join person B on A.id = B.id where email = '$myusername and pass_word = $mypassword"
        $result = mysqli_query($conn, $sql);
        if (mysqli_num_rows($result) === 1) {
            $row = mysqli_fetch_assoc($result);
            if ($row['email'] === $uname && $row['pass_word'] === $pass) {
                echo "Logged in!";
                $_SESSION['email'] = $row['email'];
                // $_SESSION['name'] = $row['name'];
                // $_SESSION['id'] = $row['id'];
                header("Location: ../public_html/about.html");
                exit();
            }else{
                header("Location: ../public_html/about.html?error=Incorect User name or password");
                exit();
            }
        }else{
            header("Location: ../public_html/about.html?error=Incorect User name or password");
            exit();
        }
    }

}else{
    header("Location: about.html");
    exit();
}
