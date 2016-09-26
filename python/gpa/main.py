# -*- coding: iso-8859-1 -*-

from lxml.html import parse
from pandas.io.parsers import TextParser

if __name__ == '__main__':
    # Load HTML data 
    parsed = parse('grade.html')
    doc = parsed.getroot()

    # Find all tables
    tables = doc.findall('.//table')
    
    grade_table = tables[0]
    
    
    rows = grade_table.findall('.//tr')
    
    grade_book = []
    
    for index in xrange(1, len(rows) - 1):
        # 2 rows 1 course
        if index % 2 == 0:
         
            cols = rows[index].findall('.//td')
            
            #for col in cols:
            # 1 - course name
            # 3 - course id
            # 4 - No of credit
            # 7 - Grade
            # 8 - Teacher email
            # 9 - Date
            
            course_name = cols[1].text_content().encode('utf-8').split('(')[0] 
            credit =  int(cols[4].text_content().encode('utf-8').replace(' ', '').split(',')[0])
            grade = (cols[7].text_content().encode('utf-8').replace(' ', ''))
            
            try:
                grade = int(grade)
            except: 
                pass
            
            #print course_name + " " + str(credit) + " " + str(grade)
            #print course_name + " " + str(credit) + " " + str(grade)
            
            grade_book.append([course_name,credit,grade])
            
            
    
    total_credit = 0
    total_grade = 0
    
    grade_partition = [0, 0, 0, 0 ,0, 0]    
    grade_under4_course = []
    
    # Analysis
    for course in grade_book:
        cr = course[1]
        gr = course[2]
        
        if isinstance(course[2], int): 
            total_credit += cr
            total_grade += cr*gr
            
            # Grade partition calculation
            grade_partition[gr] += 1
            
            if gr < 4:
                grade_under4_course.append(course) 
        
        
    print "GPA: " + str(round(float(total_grade) / float(total_credit), 2))
    
    print '\t'
    
    print "Grade partition: "
    for i in xrange(len(grade_partition)):
        print "\t" + str(i) + ": " + str(grade_partition[i]) + "\t" + str(round(float(grade_partition[i])/sum(grade_partition) * 100, 2)) + "%" 

    print '\t'
    
    print "Retake course(s):"
    print '%-30s%10s%10s%18s%18s' % ('Course', 'Cr', 'Gr', 'Retake - 4', 'Retake - 5')
    print '---------------------------------------------------------------------------------------'
    for under4 in grade_under4_course:
        print '%-30s%9d%10d%15.2f%19.2f' % (under4[0], under4[1], under4[2], round((float(total_grade) + (4-under4[2])*under4[1] ) / float(total_credit), 2), round((float(total_grade) + (5-under4[2])*under4[1] ) / float(total_credit), 2))
        
        
    