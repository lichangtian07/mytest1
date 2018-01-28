#! /bin/sh 

startShell='/usr/tomcat/apache-tomcat-9.0.0.M21/bin/startup.sh'
stopShell='/usr/tomcat/apache-tomcat-9.0.0.M21/bin/shutdown.sh'
cataShell='/usr/tomcat/apache-tomcat-9.0.0.M21/bin/catalina.sh'

tomcat_start(){
	#startShell
	$cataShell start
}

tomcat_stop(){
	#stopShell
	$cataShell stop
}

tomcat_cmd_handle(){
	case "$1" in 
		start)
			echo "$startShell"
			tomcat_start
			;;
		restart|reload|force-reload)
			echo "$startShell && $stopShell"
			tomcat_stop
			tomcat_start
			;;
		stop)
			echo "$stopShell"
			tomcat_stop
			;;
		*)
			echo "Usage: $0 start|stop|restart|reload" 
			;;
	esac

	exit 0 
}
tomcat_cmd_handle $1

