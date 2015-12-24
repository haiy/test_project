select buyer_id,
        --3d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-3,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_3,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-3,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_3,
        
        --7d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-7,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_7,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-7,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_7,
        
        --14d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-14,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_14,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-14,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_14,
        
        --30d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-30,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_30,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-30,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_30,
        
        --60d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-60,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_60,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-60,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_60,
        
        --90d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-90,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_90,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-90,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_90,
        
        --180d feature
        count(
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-180,'dd'),'yyyymmdd') 
            then buyer_id end)
        as m_view_times_total,
        
        count(distinct 
            case when 
                thedate <= to_char(dateadd(to_date('${task_date}','yyyymmdd'),0,'dd'),'yyyymmdd')  
                and thedate > to_char(dateadd(to_date('${task_date}','yyyymmdd'),-180,'dd'),'yyyymmdd') 
                then thedate end) 
        as m_view_days_total,
        datediff(to_date('${task_date}', 'yyyymmdd'), to_date(max(thedate), 'yyyymmdd'), 'dd' ) as m_last_view_to_now,
        datediff(to_date('${task_date}', 'yyyymmdd'), to_date(min(thedate), 'yyyymmdd'), 'dd' ) as m_first_view_to_now
    from m_new_tmp_view_data 
    group by buyer_id;
