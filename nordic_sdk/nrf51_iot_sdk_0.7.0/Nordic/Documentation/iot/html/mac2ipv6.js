(function($){
    var prefix_string = "fe80";
    var mac   = "";
    var car   = 0;

    String.prototype.isMAC = function() {
            regex = /\b([A-F0-9]{2}:){5}([A-F0-9]{2})\b/i ;
            return regex.test(this.toString());
    };
    String.prototype.isIpv6 = function() {
            regex = /\b([A-F0-9]{1,4}:){7}([A-F0-9]{1,4})\b/i ;
            return regex.test(this.toString());
    };
    String.prototype.isPrefix = function() {
            regex = /\b([A-F0-9]{1,4}){1}(:[0-9a-fA-F]{1,4}){0,7}\b/i ;
            return regex.test(this.toString());
    };

    function isNumber(n)
    {
        return (n >= 48 && n <= 57);
    };

    function isHexChar(n)
    {
        return (n >= 65 && n <= 70) || (n >=97 && n <= 102);
    };

    function isHex(n)
    {
        return isNumber(n) || isHexChar(n);
    };

    function isBackspace(n)
    {
        return (n == 8);
    };

    function isColon(n)
    {
        return (n == 58);
    };

    function renderPrefix(s)
    {
        var chars = s.split("");
        var result = []
        $.each(chars, function(index, value) {
            if (index < 28)
            {
                if (index > 0 && (index % 4) == 0)
                {
                    result.push(':');
                }                     
                result.push(value);
            }
        });

        return result.join("");
    };
    function renderIPv6(p)
    {
        
        var mac_elements = $('#mac').val().split(':');
        var ipv6_addr = "";
        var pre = $('#prefix').val();
        $.each(mac_elements, function(index, value){
            if (index == 0)
            {
                ipv6_addr += "02"
            }
            else
            {
                if (index % 2 == 0)
                {
                    ipv6_addr += ":";
                }
                ipv6_addr += value;    

                if (index == 2)
                {
                    ipv6_addr += "FF:FE";
                }
            }
            
        });

        $('#ipv6').val(pre.toLowerCase() + "::" + ipv6_addr.toLowerCase());

    };
    $.fn.extend({
        ipv6Address: function() {
            $(this).val(prefix_string);
        },
        prefixAddress: function() {
            $(this).val('');
            function stripString(s, c)
            {
                var re = new RegExp(c, 'g');
                return s.replace(re, '');
            };
            $(this).bind('input propertychange', function(e) {
                car = $(this).caret();

                prefix_string = stripString($(this).val(), ":");
                var length = $(this).val().length;

                if (renderPrefix(prefix_string).isPrefix())
                {
                    $(this).css({backgroundColor: '#66ff66'});
                    $(this).val(renderPrefix(prefix_string));
                    renderIPv6(renderPrefix(prefix_string)); 
                    var new_length = $(this).val().length;
                    if ((new_length - length) > 0)
                    {
                        $(this).caret(car + (new_length - length));
                    }
                    else if ((new_length - length) < 0)
                    {
                        $(this).caret(car - (new_length - length) - 1);
                    }
                    else
                    {
                        $(this).caret(car);   
                    }
                }
                else
                {
                    $(this).css('background-color', 'red');
                }
            });
        },
        macAddress: function() {
            var count = 1;
            $(this).val('');

            function renderMAC(s)
            {
                var chars = s.split("");
                var result = []
                $.each(chars, function(index, value) {
                    if (index < 12)
                    {
                        if (index > 0 && (index % 2) == 0)
                        {
                            result.push(':');
                        }                     
                        result.push(value);
                    }
                });

                return result.join("");
            };

            function stripString(s, c)
            {
                var re = new RegExp(c, 'g');
                return s.replace(re, '');
            };

            $(this).bind('input propertychange', function(e) {
                mac = stripString($(this).val(), ":");
                

                if (renderMAC(mac).isMAC())
                {
                    $(this).css({backgroundColor: '#66ff66'});
                    $(this).val(renderMAC(mac));
                    renderIPv6(renderPrefix(prefix_string)); 
                }
                else
                {
                    $(this).css('background-color', 'red');
                }
            });
        }
    });//$.fn.extends
})(jQuery);