
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

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

public class MyTest{
    public static void main(String [] args){
        Calendar r = Calendar.getInstance();
        String s1= "123 234";
        String [] res = s1.split(" ");

        ArrayList<ArrayList<Integer>> ta = new ArrayList<ArrayList<Integer>>();
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                ta.add(new ArrayList<Integer>());
                ta.get(i).add(i*j);
            }
        }

        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                System.out.print(ta.get(i).get(j));
            }
            System.out.println();
        }

        String host = "test.com";
        String targetHost = "hasdllotest.com.sad";
        for (int i=0; i<=(targetHost.length() - host.length()); i++){
            if(targetHost.regionMatches(i, host, 0, host.length())){
                System.out.println("Found it");
            }
        }


        Map<String, String> mres = new HashMap<String, String>();
        System.out.println(mres.get("cna"));
        String m1 = mres.get("cna");
        if ( m1 == null){
            System.out.println("nulllllllllrllll");
        }
        String Get = "GET/app.gif?\u0026cna\u003dby3gCyjgVEgCAW6s0SQxbHYc HTTP/1.1";
        String pattten = "(GET.*?cna=)([0-9a-zA-Z]+)( HTTP.*)";
        Pattern pr = Pattern.compile(pattten);
        Matcher pm = pr.matcher(Get);
        if (pm.find()){
            System.out.println("Here............" + pm.group(2));
        }
        String req = "712; caa\u003da8iKCdctMnYCAXehsgMcTB25; BAIDUID\u003de%3D1%26p%3D*%26s%3D0%26c%3D0%26f%3D0%26g%3D0%26t%3D0; lzstat_uv\u003d2096601802286456882|2199358@878758@1813784@2976755; t\u003d4529c62d05002c23bac21c80983da4c7" ;
        System.out.println(Get);
        System.out.println(Long.valueOf(res[0]+res[1]));
        System.out.println(r);
        System.out.println(r.get(1));
        System.out.println(r.getTimeInMillis());
        long mt = r.getTimeInMillis();
        String val = "1398433425836";
        System.out.println(val.length());
        System.out.println("nano " + (new Timestamp(mt)).getNanos());
        Long tD = Long.valueOf("1398433425836082");

        tD = tD/1000;
        System.out.println("td  " + tD);
        String ts = "1398487425783";
        //long miT = TimeUnit.MILLISECONDS.convert(Long.valueOf(ts), TimeUnit.NANOSECONDS );
        //tD = Long.valueOf(ts.split(" ")[0]) + Long.valueOf(ts.split(" ")[1]);
        Date d = new Date(tD);
        System.out.print((new SimpleDateFormat("yyyy-MM-dd HH:mm:ss,SSS")).format(d) + ",");

        System.out.println("Here " + TimeUnit.SECONDS.toMillis(1));

        List<HashMap<String, String>> info = new ArrayList<HashMap<String, String>>();
        HashMap tmp = new HashMap<String, String>();
        tmp.put("key", String.valueOf(1));
        info.add(tmp);

        tmp = new HashMap<String, String>();
        tmp.put("key", String.valueOf(3));
        info.add(tmp);

        tmp = new HashMap<String, String>();
        tmp.put("key", String.valueOf(2));
        info.add(tmp);

        Collections.sort(info, new Comparator<Map<String, String>>(){
            public int compare(Map<String, String> a, Map<String, String> b){
                return Integer.valueOf(a.get("key")) - Integer.valueOf(b.get("key"));
            }
        });

        for (Map<String, String> a : info){
            System.out.println("key :" + a.get("key"));
        }

        String aSub = "abcd";
        System.out.println("Substring:" + val.substring(0,13));
        long sec = 1398433425;
        Date ds = new Date(sec*10);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss,SSS", Locale.ENGLISH);
        sdf.setTimeZone(TimeZone.getTimeZone("UTC"));
        System.out.println("time " + (sdf.format(ds) + ","));

        System.out.println("=========================================");
        try{
            URL testUrl = new URL("http://toruk.tanx.com/ex?i=mm_16143929_2253494_15450510&cb=jsonp_callback_39907&callback=&userid=&o=&f=&n=&re=1920x1080&r=&cah=1056&caw=1920&ccd=24&ctz=8&chl=2&cja=1&cpl=2&cmm=3&cf=14.0&cg=ab3937c7fa000313edc250afd2257409&pvid=d593fd041698454be9021cd6dc2da83c&ai=0&ac=7869&prn=19693218&cas=prn&cbh=250&cbw=300&dx=1&u=http%3A%2F%2Fwww.163.com%2F&k=&tt=");

            URL debugUrl = new URL("http://t11.baidu.com/cpro/ui/uijs.php?rs=0&tu=u1481282&tn=template_inlay_all_mobile&n=163jiankang_cpradn=1&rsi1=80&rsi0=320&rad=&rss0=&rss1=&conOP=0&rss2=&rss3=&rss4=&rss5=&rss6=&rsi5=4&ts=1&at=97&ch=0&cad=1&aurl=&rss7=&cpa=1&fv=0&cn=0&if=16&word=http%3A%2F%2Fm.163jiankang.com%2F%3Fsrc%3http%3A%2F%2Fwww.163jiankang.com%2Fsex%2Findex.html&refer=&ready=3&jk=99ee68e1bb811368&jn=3&lmt=1398327362&csp=480800&csn=480800&ccd=24&chi=3&cja=false&cpl=0&cmi=0&cce=true&csl=zh-CN&did=&rt=31&dt=1398356163&pn=1|template_inlay_all_mobile|99&ev=16777216&c01=0&prt=1398356161758&i3=f&anatp=0&stid=0&distp=1001&lunum=0&scale=20.5&skin=mobile_skin_white_blue&extra=20.5&originUl=http%3A%2F%2Fwww.163jiankang.com%2Fsex%2Findex.html&pl=4&conW=320&conH=80");
            //String decodeUrl = URLDecoder.decode("http://t11.baidu.com/cpro/ui/uijs.php?rs=0&tu=u1481282&tn=template_inlay_all_mobile&n=163jiankang_cpradn=1&rsi1=80&rsi0=320&rad=&rss0=&rss1=&conOP=0&rss2=&rss3=&rss4=&rss5=&rss6=&rsi5=4&ts=1&at=97&ch=0&cad=1&aurl=&rss7=&cpa=1&fv=0&cn=0&if=16&word=http%3A%2F%2Fm.163jiankang.com%2F%3Fsrc%3http%3A%2F%2Fwww.163jiankang.com%2Fsex%2Findex.html&refer=&ready=3&jk=99ee68e1bb811368&jn=3&lmt=1398327362&csp=480800&csn=480800&ccd=24&chi=3&cja=false&cpl=0&cmi=0&cce=true&csl=zh-CN&did=&rt=31&dt=1398356163&pn=1|template_inlay_all_mobile|99&ev=16777216&c01=0&prt=1398356161758&i3=f&anatp=0&stid=0&distp=1001&lunum=0&scale=20.5&skin=mobile_skin_white_blue&extra=20.5&originUl=http%3A%2F%2Fwww.163jiankang.com%2Fsex%2Findex.html&pl=4&conW=320&conH=80", "UTF-8");
            //System.out.println(decodeUrl);
            //URL posURL = new URL("http://pos.baidu.com/ecom?di=u1603179&dcb=BAIDU_DUP2_define&dtm=BAIDU_DUP2_SETJSONADSLOT&dbv=2&dci=0&dri=0&dis=3&dai=1&dds=&drs=1&dvi=1406797944&ltu=http%3A%2F%2Fwww.163.com%2F&liu=http%3A%2F%2Fimg1.126.net%2Fchannel4%2F015788%2Fbaidu640100_0630.html&ltr=http%3A%2F%2Fwww.163.com%2F&lcr=http%3A%2F%2Fnews.163.com%2Fapi%2F14%2F0708%2F09%2FA0KDV6FG00011229.html%3Fhl&ps=0x0&psr=1920x1080&par=1920x1056&pcs=640x100&pss=640x100&pis=640x100&cfv=14&ccd=24&chi=2&cja=true&cpl=2&cmi=3&cce=true&col=en-US&cec=UTF-8&cdo=-1&tsr=8&tlm=1404082627&tcn=1407206457&tpr=1407206456669&dpt=none&coa=rs%3D60004&baidu_id=");
            //String pos_req_url = "http://pos.baidu.com/ecom?cec=gb2312&dai=1&cfv=13&cpa=1&col=zh-cn&dis=3&xuanting=0&n=38091079_cpr&conOP=0&scale=&skin=&rsi0=300&rsi1=250&rsi5=4&ltr=http%3A%2F%2Fwar.163.com%2F14%2F0425%2F07%2F9QLMELNF00011MTO.html&ltu=http%3A%2F%2Fwar.163.com%2F14%2F0425%2F07%2F9QLMELNF00011MTO.tml&pcs=300x250&rss0=%23FFFFFF&rss1=%23FFFFFF&rss2=%230000FF&rss3=%23444444&rss4=%23008000&rss5=&rss6=%23e10900&rss7=&rad=&pis=300x250&aurl=&psr=1920x1080&pss=300x250&tpr=1398398627734&num=6&ch=0&at=6&qn=179cf4531ffef454&ps=-4x-4&tn=text_default_300_250&ts=1&c01=0&td_id=1445684&adn=3&cad=1&ccd=32&dtm=BAIDU_DUP2_SETJSONADSLOT&dc=2&di=u1445684||";

            //String qString = debugUrl.toURI().getQuery();
            //String qString = testUrl.toURI().getQuery();
            //String pos_req_url = "/2.gif?logtype=1&title=LG%20WD-T12410D%208%u516C%u65A4/%u53D8%u9891/%u5168%u81EA%u52A8/%u6EDA%u7B52/%u6D17%u8863%u673A/1200%u8F6C-tmall.com%u5929%u732B&pre=http%3A%2F%2Flist.tmall.com%2Fsearch_product.htm%3Fspm%3Da220m.1000858.1000722.13.usmn8%26cat%3D50918005%26prop%3D34111%3A493262400%26sort%3Ds%26style%3Dg%26search_condition%3D71%26auction_tag%3D7809%26from%3Dsn_1_prop%26suggest%3D0_1%26active%3D1%26industryCatId%3D5018005&cache=5b7d1dd&scr=1024x768&isbeta=7&cna=yt+5C6z3UXcCAa8Z8ONAXmuF&nick=wjstpqhd622&wm_pageid=300114162&wm_prototypeid=2&wm_sid=101954690&spm-url=a220m.1000858.1000725.13.GWxBjc&spm-re=a220m.1000858.1000722.13.husmn8&spm-cnt=a220o.1000855.0.0.CkXib&category=item%5f350301&uidaplus=677137075&at_isb=1&at_bucketid=sbucket%5f0&b2c_brand=10428&b2c_auction=19972278765&at_autype=4%5f101954690&aplus&yunid=&asid=AAFqNllTawYddvIYO+c=";
            URL posURL = new URL(pos_req_url);
            String qString = URLDecoder.decode(posURL.getQuery(), "UTF-8");

            String qString2 = new URL(URLDecoder.decode(pos_req_url,"UTF-8")).getQuery();
            System.out.println("============" +qString);
            qString += qString2;

            Pattern httpPattern = Pattern.compile("=(http://.*?)&");
            Matcher hM = httpPattern.matcher(qString);
            while (hM.find()){
                System.out.println("Here " + hM.group(1));
            }
            Gson gson = new Gson();
            Path file = FileSystems.getDefault().getPath(".", "GsonTest.data");
            Charset charset = Charset.forName("UTF-8");
            try (BufferedReader reader = Files.newBufferedReader(file, charset)) {
                String line = null;
                while ((line = reader.readLine()) != null) {
                    Map<String, String> reqMap = gson.fromJson(line, new TypeToken<Map<String, String>>() {
                    }.getType());
                    String tur = reqMap.get("TS");
                    System.out.println(tur);
                    String test_url_req = new URL("http://" + reqMap.get("GET").split(" ")[0]).getQuery();
                    System.out.println(test_url_req);
                    String test_url_ref = new URL(URLDecoder.decode(reqMap.get("Referer"), "UTF-8")).getQuery();
                    System.out.println(test_url_ref);
                    System.out.println("==============");

                }
            } catch (IOException x) {
                System.err.format("IOException: %s%n", x);
            }
        }
        catch( UnsupportedEncodingException | MalformedURLException  e){
            System.out.println(e);
        }

        List<String> a = new ArrayList<String>();
        a.addAll(AddStringTest.get());
        for (String s :a ){
            System.out.println(s);
        }
        a.removeAll(null);
        a.add("Onely");
        for (String s :a ){
            System.out.println(s);
        }

    }
}

class AddStringTest{
    public static List<String> get(){
        List<String> a = new ArrayList<String>();
        return a;
    }
}
