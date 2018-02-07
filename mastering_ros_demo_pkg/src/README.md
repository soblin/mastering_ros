In demo_topic programms, the publisher publishes 1, 2, 3, ,,, to "/demo_topic_publisher_topic".
In demo_msg programms, the publisher publishes arrays of custom data in the form of
```
msg = [{str1, int, uint, str2, float, bool}
      ,{str1, int, uint, str2, float, bool}
      ,{str1, int, uint, str2, float, bool}
      ,{str1, int, uint, str2, float, bool}]
```
In demo_service pragramms, the clinet sends 1, 3, 5 ,7, 9, ,,, to the server. If the number is divisible by 3 or includes 3, the server sends special mesagees.
