<!--
<start name="ptcp_test" caps="1200" priority="-1">
    <resource name="RAM" quantum="100M"/>
        <route>
            <service name="Nic"> <child name="nic_router"/> </service>
            <service name="SIG_SNAP"> <child name="snapshot_notifier"/> </service>
            <service name="Block"> <child name="ahci_drv"/> </service>
            <any-service> <parent/> <any-child/> </any-service>
        </route>
    <config  verbose="yes" ld_verbose="yes" >
        <vfs>
            <dir name="snapshot"> <rump fs="ext2fs" ram="10M"/> </dir>
            <dir name="dev"><log/> </dir>
            <dir name="socket"> <ptcp dhcp="yes"/> </dir>
        </vfs>
        <libc stdout="/dev/log" stderr="/dev/log" socket="/socket"/>
    </config>
</start>
-->