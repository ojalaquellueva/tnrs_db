CREATE TABLE source (
  sourceID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  sourceName VARCHAR(50) NOT NULL UNIQUE,
  sourceNameFull VARCHAR(250) DEFAULT NULL,
  sourceUrl VARCHAR(500) DEFAULT NULL,
  description text,
  geographic_scope VARCHAR(50) DEFAULT NULL, 
  taxonomic_scope VARCHAR(50) DEFAULT NULL, 
  `scope` VARCHAR(50) DEFAULT NULL, ` 
  logo_path VARCHAR(500) DEFAULT NULL,    
  dataUrl VARCHAR(500) DEFAULT NULL,   
  sourceVersion VARCHAR(100) DEFAULT NULL,
  sourceReleaseDate DATE DEFAULT NULL,
  dateAccessed DATE DEFAULT NULL,
  citation TEXT DEFAULT NULL, 
  isDefault  INTEGER(1) UNSIGNED NOT NULL DEFAULT 0,
  isHigherClassification INTEGER(1) UNSIGNED NOT NULL DEFAULT 0,
  warning INTEGER(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY(sourceID),
  INDEX source_sourceName(sourceName),
  INDEX source_isDefault(isDefault),
  INDEX source_geographic_scope(geographic_scope),
  INDEX source_taxonomic_scope(taxonomic_scope),
  INDEX source_scope(`scope`),
  INDEX source_isHigherClassification(isHigherClassification),
  INDEX source_warning(warning)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE name (
  nameID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  bestFuzzyMatchID INTEGER UNSIGNED DEFAULT NULL,
  originalSourceID INTEGER UNSIGNED DEFAULT NULL,
  nomenclaturalCode VARCHAR(25) DEFAULT NULL,
  scientificName VARCHAR(150) NOT NULL,
  scientificNameAuthorship VARCHAR(150) DEFAULT NULL,
  nameRank VARCHAR(25) DEFAULT NULL,
  nameParts INTEGER(1) DEFAULT NULL,
  namePublicationYear INTEGER UNSIGNED DEFAULT NULL,
  taxonomicStatus VARCHAR(250) DEFAULT NULL,
  taxonRemarks VARCHAR(250) DEFAULT NULL,
  scientificNameWithAuthor VARCHAR(300) NOT NULL,
  genusHybridX VARCHAR(1) DEFAULT NULL,
  genus VARCHAR(100) DEFAULT NULL,
  speciesHybridX VARCHAR(1) DEFAULT NULL,
  specificEpithet VARCHAR(100) DEFAULT NULL,
  rankIndicator VARCHAR(25) DEFAULT NULL COMMENT 'Rank abbreviation used to form name string, if applicable',
  infraspecificHybridX VARCHAR(1) DEFAULT NULL,
  infraspecificEpithet VARCHAR(100) DEFAULT NULL,
  infraspecificHybridX2 VARCHAR(1) DEFAULT NULL,
  infraspecificRank2 VARCHAR(25) DEFAULT NULL,
  infraspecificEpithet2 VARCHAR(100) DEFAULT NULL,
  otherEpithet VARCHAR(100) DEFAULT NULL COMMENT 'Epithets for tribe, section, etc.',
  isHybrid INT(1) NOT NULL DEFAULT 0,
  isNamedHybrid INT(1) DEFAULT NULL DEFAULT 0,
  isHybridFormula INT(1) DEFAULT NULL DEFAULT 0,
  defaultFamily VARCHAR(100) DEFAULT NULL,
  PRIMARY KEY(nameID),
  INDEX name_bestFuzzyMatchID(bestFuzzyMatchID),
  INDEX name_originalSourceID(originalSourceID),
  INDEX name_nomenclaturalCode(nomenclaturalCode),
  INDEX name_scientificName(scientificName),
  INDEX name_scientificNameAuthorship(scientificNameAuthorship),
  INDEX name_nameRank(nameRank),
  INDEX name_nameParts(nameParts),
  INDEX name_taxonomicStatus(taxonomicStatus),
  INDEX name_scientificNameWithAuthor(scientificNameWithAuthor),
  INDEX name_isHybrid(isHybrid),
  INDEX name_genus(genus),
  INDEX name_specificEpithet(specificEpithet),
  INDEX name_otherEpithet(otherEpithet),
  INDEX name_rankIndicator(rankIndicator),
  INDEX name_infraspecificEpithet(infraspecificEpithet),
  INDEX name_infraspecificRank2(infraspecificRank2),
  INDEX name_infraspecificEpithet2(infraspecificEpithet2),
  INDEX name_defaultFamily(defaultFamily)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE name_source (
  nameSourceID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  nameID INTEGER UNSIGNED NOT NULL,
  sourceID INTEGER UNSIGNED NOT NULL,
  nameSourceUrl VARCHAR(250) DEFAULT NULL,
  lsid VARCHAR(500) DEFAULT NULL,
  nameSourceOriginalID VARCHAR(250) DEFAULT NULL,
  dateAccessed DATE DEFAULT NULL,
  dateCreated TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY(nameSourceID),
  INDEX nameSource_nameSourceOriginalID(nameSourceOriginalID),
  INDEX nameSource_FKIndex1(nameID),
  INDEX nameSource_FKIndex2(sourceID),
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(sourceID) REFERENCES source(sourceID) ON DELETE RESTRICT ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE classification (
  classificationID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  sourceID INTEGER UNSIGNED NOT NULL,
  nameID INTEGER UNSIGNED NOT NULL,
  parentNameID INTEGER UNSIGNED DEFAULT NULL,
  family VARCHAR(100) DEFAULT NULL COMMENT 'family according to this source',
  leftIndex INTEGER UNSIGNED DEFAULT NULL,
  rightIndex INTEGER UNSIGNED DEFAULT NULL,
  joinMethod VARCHAR(50) DEFAULT NULL,
  PRIMARY KEY(classificationID),
  INDEX classification_sourceID(sourceID),
  INDEX classification_nameID(nameID),
  INDEX classification_family(family),
  INDEX classification_leftIndex(leftIndex),
  INDEX classification_rightIndex(rightIndex),
  INDEX classification_joinMethod(joinMethod),
  FOREIGN KEY(parentNameID) REFERENCES name(nameID) ON DELETE RESTRICT ON UPDATE CASCADE,
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(sourceID) REFERENCES source(sourceID) ON DELETE RESTRICT ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


CREATE TABLE `synonym` (
  synonymID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  sourceID INTEGER UNSIGNED NOT NULL,
  nameID INTEGER UNSIGNED NOT NULL,
  acceptedNameID INTEGER UNSIGNED DEFAULT NULL,
  acceptance VARCHAR(50) DEFAULT NULL,
  nomenclaturalStatusRemarks VARCHAR(100) DEFAULT NULL,
  synonymType VARCHAR(250) DEFAULT NULL,
  synonymSourceUrl VARCHAR(250) DEFAULT NULL,
  citation TEXT DEFAULT NULL, 
  PRIMARY KEY(synonymID),
  INDEX synonym_acceptedNameID(acceptedNameID),
  INDEX synonym_acceptance(acceptance),
  INDEX synonym_nomenclaturalStatusRemarks(nomenclaturalStatusRemarks),
  INDEX synonym_nameID(nameID),
  INDEX synonym_sourceID(sourceID),
  INDEX synonym_synonymType(synonymType),
  FOREIGN KEY(nameID) REFERENCES name(nameID) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY(sourceID) REFERENCES source(sourceID) ON DELETE RESTRICT ON UPDATE CASCADE
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

CREATE TABLE `meta` (
  meta_id INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  app_version VARCHAR(50) DEFAULT NULL,
  db_version VARCHAR(50) DEFAULT NULL,
  build_date DATE NOT NULL,
  db_code_version VARCHAR(50) DEFAULT NULL,
  code_version VARCHAR(50) DEFAULT NULL,
  api_version VARCHAR(50) DEFAULT NULL,
  citation TEXT DEFAULT NULL, 
  publication TEXT DEFAULT NULL,
  logo_path VARCHAR(500) DEFAULT NULL,
  PRIMARY KEY(meta_id)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

DROP TABLE IF EXISTS collaborator;
CREATE TABLE collaborator (
  collaboratorID INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  collaboratorName VARCHAR(50) NOT NULL UNIQUE,
  collaboratorNameFull VARCHAR(250) DEFAULT NULL,
  collaboratorUrl VARCHAR(500) DEFAULT NULL,
  description text,
  logo_path VARCHAR(500) DEFAULT NULL,
  PRIMARY KEY(collaboratorID),
  INDEX collaborator_collaboratorName(collaboratorName)
)
ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



