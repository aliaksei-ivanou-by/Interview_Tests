<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:tr="http://www.opentravel.org/OTA/2003/05" exclude-result-prefixes="tr"
  xmlns:str="http://exslt.org/strings">
  <xsl:output method="xml" version="1.0" encoding="UTF-8" indent="yes" omit-xml-declaration="yes"/>

  <!-- 7. Все атрибуты и элементы, неупомянутые выше, скопировать без изменений -->
  <xsl:template match="node() | @*">
    <xsl:copy>
      <xsl:apply-templates select="node() | @*"/>
    </xsl:copy>
  </xsl:template>

  <!-- 1. Элементы 'ContactInfo', 'MultimediaDescription' и 'ImageFormat' должны быть удалены, 
    их потомки поднимаются на уровень выше (т.е. просто теряют родителя) -->
  <xsl:template match="tr:ContactInfo">
    <xsl:apply-templates select="node() | @*"/>
  </xsl:template>
  <xsl:template match="tr:MultimediaDescription">
    <xsl:apply-templates select="node() | @*"/>
  </xsl:template>
  <xsl:template match="tr:ImageFormat">
    <xsl:apply-templates select="node() | @*"/>
  </xsl:template>

  <!-- 2. Элементы, в имени которых встречается сочетание 'rds', должны быть удалены, 
    с переносом их дочерних элементов на уровень выше -->
  <xsl:template match="*[(contains(local-name(), 'rds'))]">
    <xsl:apply-templates select="node() | @*"/>
  </xsl:template>


  <!-- 4. Если элемент содержит несколько дочерних элементов 'Description', 
    вывести следует только один, который содержит самый длинный текст -->
  <xsl:template match="node() | @*">
    <xsl:copy>
      <xsl:apply-templates select="@* | node()"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="tr:Description">
    <xsl:if test="not(preceding-sibling::tr:Description)">
      <xsl:for-each select="../tr:Description">
        <xsl:sort select="string-length(.)" data-type="number" order="descending"/>
        <xsl:if test="position() = 1">
          <xsl:copy>
            <xsl:apply-templates select="node() | @*"/>
          </xsl:copy>
        </xsl:if>
      </xsl:for-each>
    </xsl:if>
  </xsl:template>

  <!-- 5. Встречающиеся в тексте символы ©, ¶, ∑, Œ  - удалить -->
  <xsl:template match="@* | node()">
    <xsl:copy>
      <xsl:apply-templates select="@* | node()"/>
    </xsl:copy>
  </xsl:template>

  <xsl:template match="text()">
    <xsl:variable name="removeChar1">
      <xsl:call-template name="removeChars">
        <xsl:with-param name="outputString" select="."/>
        <xsl:with-param name="target" select="'©'"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="removeChar2">
      <xsl:call-template name="removeChars">
        <xsl:with-param name="outputString" select="$removeChar1"/>
        <xsl:with-param name="target" select="'¶'"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="removeChar3">
      <xsl:call-template name="removeChars">
        <xsl:with-param name="outputString" select="$removeChar2"/>
        <xsl:with-param name="target" select="'∑'"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:variable name="removeChar4">
      <xsl:call-template name="removeChars">
        <xsl:with-param name="outputString" select="$removeChar3"/>
        <xsl:with-param name="target" select="'Œ'"/>
      </xsl:call-template>
    </xsl:variable>
    <xsl:value-of select="$removeChar4"/>
  </xsl:template>

  <xsl:template name="removeChars">
    <xsl:param name="outputString"/>
    <xsl:param name="target"/>
    <xsl:param name="replacement"/>
    <xsl:choose>
      <xsl:when test="contains($outputString, $target)">
        <xsl:value-of select="concat(substring-before($outputString, $target), $replacement)"/>
        <xsl:call-template name="removeChars">
          <xsl:with-param name="outputString" select="substring-after($outputString, $target)"/>
          <xsl:with-param name="target" select="$target"/>
          <xsl:with-param name="replacement" select="$replacement"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="$outputString"/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <!-- 6. Элемент 'DescriptiveText' перевести в аттрибут, элемента 'Service' -->
  <!-- Не работает
  <xsl:template match="*[tr:DescriptiveText]">
    <xsl:copy>
      <xsl:attribute name="DescriptiveText">
        <xsl:value-of select="tr:DescriptiveText"/>
      </xsl:attribute>
      <xsl:apply-templates/>
    </xsl:copy>
  </xsl:template>
  -->

  <!-- 3. Атрибут 'Caption', должен стать дочерним элементом (своего элемента) -->
  <xsl:template match="@Caption">
    <xsl:element name="{local-name()}" namespace="{namespace-uri(..)}">
      <xsl:value-of select="."/>
    </xsl:element>
  </xsl:template>


</xsl:stylesheet>