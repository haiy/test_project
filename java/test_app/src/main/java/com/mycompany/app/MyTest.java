package com.mycompany.app;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLDecoder;
import java.net.URLEncoder;
import java.nio.charset.Charset;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.sql.Timestamp;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.concurrent.TimeUnit;
import java.text.SimpleDateFormat;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaSparkContext;


public class MyTest{
    public static void main(String [] args){
        SparkConf conf = new SparkConf().setAppName("Test");
        JavaSparkContext sc = new JavaSparkContext(conf);
        TestStaticMap.v.add("nimeem");
        System.out.println(TestStaticMap.v);
        Date dt = new Date();
        long ts = new Timestamp(dt.getTime()).getTime();
        System.out.println("Now ts :" + ts + "\n");
        System.out.println(new Timestamp(new Date().getTime()).getTime());
        long t1 = System.currentTimeMillis();
        System.out.println(t1);

        System.out.println("HashCode of String :  " + String.valueOf("nimiei(*&678712039808*&^*^&*09812348973209JKJHIIUHi7666666666666623hbg&*%&%^&*& 8wsfddehahscode".hashCode()));

        List<Integer> dataList = new ArrayList<>();
        for (int i = 0; i < 100000; i++) {
            dataList.add(i);
        }

        List<String> del = Arrays.asList("com", "cn", "net");
        String h = "www.astwedfas.asdq2daq.nimei.com.cn.net";
        List<String> strList = Arrays.asList(h.split("\\."));
        System.out.println(strList + "\t" + strList.size());

        int i = 1;
        while (del.contains(strList.get( (strList.size()-i)))) {
            i ++;
        }
        System.out.println(strList + "\t" + strList.get(strList.size()-i));

        HashMap<String, String> putTest = new HashMap<>();
        putTest.put("Nimei", "NIMEI");
        System.out.println(putTest);
        putTest.put("Nimei", "M");
        System.out.println(putTest);
        Map<String, String> map = new HashMap<String, String>();
        while(true){
            map.put("avasfasdsfdsfsdfdsfsdf","asdddddddddddddddddddddddddddddddddddddddddsssssssssddd");
        }


    }

    public static void test(String [] args) throws MalformedURLException,URISyntaxException {
        {
            String testUrl = ("http://toruk.tanx.com/ex?i=mm_16143929_2253494_15450510&cb=jsonp_callback_39907&callback=&userid=&o=&f=&n=&re=1920x1080&r=&cah=1056&caw=1920&ccd=24&ctz=8&chl=2&cja=1&cpl=2&cmm=3&cf=14.0&cg=ab3937c7fa000313edc250afd2257409&pvid=d593fd041698454be9021cd6dc2da83c&ai=0&ac=7869&prn=19693218&cas=prn&cbh=250&cbw=300&dx=1&u=http%3A%2F%2Fwww.163.com%2F&k=&tt=");
            String t = "a";
            String ckTest = "Cookie: cna=uwrJC78zgE0CAXzK47aPqFXi; otherx=e%3D1%26p%3D*%26s%3D0%26c%3D0%26f%3D0%26g%3D0%26t%3D0; x=__ll%3Dc812a92831e53da2c73c61c8c8af8942true%26_ato%3D0;                                   t=c812a92831e53da2c73c61c8c8af8942; uc3=nk2=F5RHoWD8uegNNQ%3D%3D&id2=UoYai9th9J7nUw%3D%3D&vt3=F8dATHqQ9x8iJI4Inq4%3D&lg2=U%2BGCWk%2F75gdr5Q%3D%3D; lgc=tb20134117; tracknick=tb20134117;        cookie2=0633517db53c97579b036042cc23ab32; uc1=cookie15=W5iHLLyFOGW7aA%3D%3D&existShop=false; cookie1=VTwrKJWT6CS4jPInM1uCwfiDEXd4wtcXdaE3Pgmtlzw%3D; unb=1740560699; _l_g_=Ug%3D%3D;            _nk_=tb20134117; cookie17=UoYai9th9J7nUw%3D%3D; _tb_token_=uN6sGoZmEn; login=true; whl=5%262%261398410625649%261398410453590^M";
            String  bdTest = " BAIDU_WISE_UID=A74308D52231AF495D62946C75E3A7E1; locale=zh; MCITY=-%3A; BAIDUID=362313F08A4B58C54D338B354E72508B:FG=1; ";
            System.out.println(t.indexOf("cna="));
            int indexPos = ckTest.indexOf("cna=") ;
            int indexBD = bdTest.indexOf("BAIDUID=") ;
            if(indexPos != -1){
                System.out.println(ckTest.substring(indexPos+4, indexPos+28));
            }
            if(indexBD != -1){
                System.out.println(indexBD);
                System.out.println(bdTest.substring(indexBD+8, indexBD+40));
            }
            System.out.println(ckTest.indexOf("cna="));
            System.out.println(Arrays.asList(t.split("\\?")).size());
            System.out.println(new Timestamp(new Date().getTime()).getTime());
            System.out.println(Integer.valueOf("2").compareTo(Integer.valueOf("1")));

            List<String> testObjectEqual = Arrays.asList("as", "as", "test");
            System.out.println(testObjectEqual.indexOf("as"));
            System.out.println("miaozhen.com".equals("miaozhen.com" + ""));

            // simple tree map
            List<Map<String, String>> treeMap = new ArrayList<Map<String, String>>();
            Map<Integer, ArrayList<Integer>> index = new HashMap<Integer, ArrayList<Integer>>();
            System.out.println(treeMap);
            NodeAction.addNode(0, "nimei", treeMap, index);
            NodeAction.addNode(2, "nimei", treeMap, index);
            NodeAction.addNode(4, "nimei", treeMap, index);
            NodeAction.addNode(1, "nimei", treeMap, index);
            System.out.println(treeMap);
            NodeAction.delNode(0, treeMap, index);
            System.out.println(treeMap);
        }
    }
}

class NodeAction{
    public static Boolean addNode(Integer father, String value, List<Map<String, String>> tree, Map<Integer, ArrayList<Integer>> index ){
        try {
            Map<String, String> node =  new HashMap<String, String >();
            node.put("v", value);
            node.put("f", String.valueOf(father));
            if(index.get(father) == null){
                index.put(father, new ArrayList<Integer>());
            }
            index.get(father).add(Integer.valueOf(tree.size()));
            tree.add(node);
            return true;

        } catch(Exception e){
            e.printStackTrace();
            return false;
        }
    }

    public static Boolean delNode(Integer father, List<Map<String, String>> tree, Map<Integer, ArrayList<Integer>> index ){
        try {
            List<Map<String, String>> delNodes = new ArrayList<>(); 
            for(Integer i : index.get(father)){
                delNodes.add(tree.get(i.intValue()));
            }
            tree.removeAll(delNodes);
            return true;

        } catch(Exception e){
            e.printStackTrace();
            return false;
        }
    }
}

class TestStaticMap{
    public static Set<String> v = new HashSet<String>();
}
