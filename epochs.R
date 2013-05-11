magI 	<- read.table("magA.dat")
magII 	<- read.table("magB.dat")
magIII 	<- read.table("magC.dat")

epochs 	<- 1890:2015
##i <- 1890
##epochs <- c()
##while (i < 2016) {
##	epochs <- cbind(epochs, i)
##	i <- i +5
##}


ra_sig_magI 		<- c()
dec_sig_magI 	<- c()
ra_sig_magII 	<- c()
dec_sig_magII	<- c()
ra_sig_magIII 	<- c()
dec_sig_magIII	<- c()

##for (i in epochs) {
## write.table(mean(sqrt(magI[,1]^2+(i-magI[,5])^2*magI[,3]^2)),file="ra_sig_magI.dat",append=TRUE)
##}





## ra rangeA
ra_sig_magI <- c()
for (i in epochs)
ra_sig_magI <- rbind(ra_sig_magI,mean(sqrt(magI[,1]^2+(i-magI[,5])^2*magI[,3]^2)))



## dec rangeA
dec_sig_magI <- c()
for (i in epochs)
dec_sig_magI <- rbind(dec_sig_magI,mean(sqrt(magI[,2]^2+(i-magI[,6])^2*magI[,4]^2)))




## ra rangeB
ra_sig_magII <- c()
for (i in epochs)
ra_sig_magII <- rbind(ra_sig_magII,mean(sqrt(magII[,1]^2+(i-magII[,5])^2*magII[,3]^2)))


## dec rangeB
dec_sig_magII <- c()
for (i in epochs)
dec_sig_magII <- rbind(dec_sig_magII,mean(sqrt(magII[,2]^2+(i-magII[,6])^2*magII[,4]^2)))



## ra rangeC
ra_sig_magIII <- c()
for (i in epochs)
ra_sig_magIII <- rbind(ra_sig_magIII,mean(sqrt(magIII[,1]^2+(i-magIII[,5])^2*magIII[,3]^2)))


## dec rangeC
dec_sig_magIII <- c()
for (i in epochs)
dec_sig_magIII <- rbind(dec_sig_magIII,mean(sqrt(magIII[,2]^2+(i-magIII[,6])^2*magIII[,4]^2)))



## plotting rangeA
par(mfrow=c(1,2))
plot(epochs,ra_sig_magI)
plot(epochs,dec_sig_magI)

## plotting rangeB
par(mfrow=c(1,2))
plot(epochs,ra_sig_magII)
plot(epochs,dec_sig_magII)

## plotting rangeC
par(mfrow=c(1,2))
plot(epochs,ra_sig_magIII)
plot(epochs,dec_sig_magIII)

##  epochs  rangeA  ra
ra_sig_magI
min(ra_sig_magI)
mean(magI[,5])
max(ra_sig_magI)

##  epochs  rangeA dec
dec_sig_magI
min(dec_sig_magI)
mean(magI[,6])
max(dec_sig_magI)

## epochs rangeB ra
ra_sig_magII
min(ra_sig_magII)
mean(magII[,5])
max(ra_sig_magII)

## epochs rangeB dec
dec_sig_magII
min(dec_sig_magII)
mean(magII[,6])
max(dec_sig_magII)

## epochs rangeC ra
ra_sig_magIII
min(ra_sig_magIII)
mean(magIII[,5])
max(ra_sig_magIII)


## epochs rangeC dec
dec_sig_magIII
min(dec_sig_magIII)
mean(magIII[,6])
max(dec_sig_magIII)



## mean min maxval minval

##for (i in epochs) {
##	ra_sig_magI <- rbind(ra_sig_magI, sqrt(magI[,1]^2+(i-magI[,5])^2*magI[,3]^2))
##	
##	dec_sig_magI <- rbind(dec_sig_magI, sqrt(magI[,2]^2+(i-magI[,6])^2*magI[,4]^2))
##	
##	ra_sig_magII <- rbind(ra_sig_magII, sqrt(magII[,1]^2+(i-magII[,5])^2*magII[,3]^2))
##	
##	dec_sig_magII <- rbind(dec_sig_magII, sqrt(magII[,2]^2+(i-magII[,6])^2*magII[,4]^2))
##	
##	ra_sig_magIII <- rbind(ra_sig_magIII, sqrt(magIII[,1]^2+(i-magIII[,5])^2*magIII[,3]^2))
##	
##	dec_sig_magIII <- rbind(dec_sig_magIII, sqrt(magIII[,2]^2+(i-magIII[,6])^2*magIII[,4]^2))
##
##}

##print(mean(magI[,5]))
##print(min(rowMeans(ra_sig_magI)))

