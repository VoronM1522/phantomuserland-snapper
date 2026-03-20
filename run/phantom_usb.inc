<!--
<start name="usb_host" ram="10M">
  <binary name="pc_usb_host"/>
  <provides><service name="Usb"/></provides>
  <config>
     <policy>
       <device vendor_id="0x8564" product_id="0x1000"/>
     </policy>
  </config>
</start>
-->



<start name="usb_sec" ram="4M">
  <binary name="usb_block"/>
  <provides> <service name="USB_Block"/> </provides>
  <config label="usb_drive" report="yes" writeable="yes" interface="0"
          alt_setting="0" lun="0" reset_device="no" verbose_scsi="no"/>
  <route>
   <service name="Usb"> <child name="usb"/> </service>
   <any-service> <parent/> <any-child/> </any-service>
  </route>
</start>



<start name="encryptor" ram="32M" caps="300">
    <config/>
    <route>
        <any-service> <parent/> <any-child/> </any-service>
    </route>
</start>

